.PHONY: clean build install do_test
.DEFAULT_GOAL := build

BUILD_DIR=./build


clean:
	@$(RM) -rf ${BUILD_DIR}

build:
	pip install -r requirements.txt
	python setup.py build

install: build
	python setup.py install

do_test: install
	nosetests tests/
