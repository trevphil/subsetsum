import sys

from pybind11 import get_cmake_dir
from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

__version__ = "0.0.1"

ext_modules = [
    Pybind11Extension("subsetsum",
        ["src/main.cpp"],
        define_macros = [("VERSION_INFO", __version__)],
        ),
]

setup(
    name="subsetsum",
    version=__version__,
    author="Trevor Phillips",
    author_email="trevphil3@gmail.com",
    url="https://github.com/trevphil/subsetsum",
    description="A Python module for finding all solutions to the SUBSET-SUM problem",
    long_description="",
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.6",
)
