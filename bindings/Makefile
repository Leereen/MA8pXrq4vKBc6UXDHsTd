.PHONY: clean build install do_test
.DEFAULT_GOAL := build

BUILD_DIR=./build


clean:
	@$(RM) -rf ${BUILD_DIR}

build:
	pip3 install -r requirements.txt
	python3 setup.py build

install: build
	python3 setup.py install

do_test: install
	nosetests tests/
