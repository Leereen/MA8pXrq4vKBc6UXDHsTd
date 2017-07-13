.PHONY: all asan build test do_test clean
.DEFAULT_GOAL := all

SHELL=/bin/bash # for arithmetic syntax AND proper ulimit parameters

BUILD_DIR=./build/
OPT_COMPILER=-DCMAKE_CXX_COMPILER=clang++
OPT_ASAN=-DASAN=ON
OPT_GTEST=-DGTEST=ON
OPT_DEBUG=-DDEBUG_MODE=ON


.mkdir:
	@mkdir -p ${BUILD_DIR}

.run_test:
	ulimit -Sm $$((1024 ** 2)) && $(SH) ./build/tests/tests

all: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} .. && $(MAKE) VERBOSE=1)

asan: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} .. && $(MAKE) VERBOSE=1)

DEBUG: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_DEBUG} .. && $(MAKE) VERBOSE=1)

test: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

asan_test: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

debug_test: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_DEBUG} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

full_test: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} ${OPT_GTEST} ${OPT_DEBUG} .. && $(MAKE) VERBOSE=1)

do_test: test .run_test

do_asan_test: asan_test .run_test

do_debug_test: debug_test .run_test

do_full_test: full_test .run_test

clean:
	@$(RM) -rf ${BUILD_DIR}

init:
	git submodule init
	git submodule update
