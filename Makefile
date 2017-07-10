.PHONY: all asan build test do_test clean
.DEFAULT_GOAL := all

BUILD_DIR=./build/
OPT_COMPILER=-DCMAKE_CXX_COMPILER=clang++
OPT_ASAN=-DASAN=ON
OPT_GTEST=-DGTEST=ON
OPT_DEBUG=-DDEBUG_MODE=ON

.mkdir:
	@mkdir -p ${BUILD_DIR}

all: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} .. && $(MAKE) VERBOSE=1)

asan: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} .. && $(MAKE) VERBOSE=1)

debug: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_DEBUG} .. && $(MAKE) VERBOSE=1)

test: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

do_test: test
	$(SH) ./build/tests/tests

asan_test: .mkdir
	@(cd ${BUILD_DIR} && cmake ${OPT_COMPILER} ${OPT_ASAN} ${OPT_GTEST} .. && $(MAKE) VERBOSE=1)

do_asan_test: asan_test
	$(SH) ./build/tests/tests

clean:
	@$(RM) -rf ${BUILD_DIR}

init:
	git submodule init
	git submodule update
