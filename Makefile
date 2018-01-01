.PHONY: all asan build test do_test clean
.DEFAULT_GOAL := all

ASAN=false

SHELL=/bin/bash # for arithmetic syntax AND proper ulimit parameters

BUILD_DIR=./build/
BINDINGS_DIR=./bindings/
TEST_DIR=${BUILD_DIR}tests/
TEST_BIN=${TEST_DIR}tests

OPT_COMPILER=-DCMAKE_CXX_COMPILER=clang++
OPT_ASAN=-DASAN=ON
OPT_GTEST=-DGTEST=ON
OPT_DEBUG=-DDEBUG_MODE=ON


.mkdir:
	@mkdir -p ${BUILD_DIR}

.run_test:
	@echo -e '\n-------- TESTING --------\n'
	@if [ ${ASAN} = true ]; \
	then \
		(ulimit -Sm $$((1024 ** 2)) && LSAN_OPTIONS=verbosity=1:log_threads=1 ASAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer) ${TEST_BIN}); \
	else \
		(cd ${TEST_DIR} && ctest); \
	fi

# TODO: Should be in .run_test, but python ctypes loader fails with asan for now
.run_python_test:
	@(cd ${BINDINGS_DIR} && $(MAKE) do_test)

all: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} .. && $(MAKE) VERBOSE=1)

asan: .mkdir
	$(eval ASAN=true)
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} .. && $(MAKE) VERBOSE=1)

debug: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_DEBUG} .. && $(MAKE) VERBOSE=1)

test: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

asan_test: .mkdir
	$(eval ASAN=true)
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

debug_test: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_DEBUG} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

full_test: .mkdir
	$(eval ASAN=true)
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} ${OPT_GTEST} ${OPT_DEBUG} .. && $(MAKE) VERBOSE=1)

do_test: test .run_test .run_python_test

do_asan_test: asan_test .run_test

do_debug_test: debug_test .run_test .run_python_test

do_full_test: full_test .run_test

clean:
	@$(RM) -rf ${BUILD_DIR}
	@$(RM) ${DEFAULT_COVERAGE_DATA} ${DEFAULT_COVERAGE_RAW}

init:
	git submodule init
	git submodule update
