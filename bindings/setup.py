# from setuptools import setup
from distutils.core import setup

setup(
    name="pathfinding",
    version="0.1.0",
    author="lpascal",
    author_email="pro.lpascal@gmail.com",
    description="Python binding other simple C++ pathfinding library",
    packages=["pathfinding"],
    package_dir={"pathfinding": "src"},
    # # TODO: auto finding & deployment of shared library
    # package_data={"pathfinding": ["../build/src/libpathfinding.so"]},
)
