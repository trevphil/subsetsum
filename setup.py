from pathlib import Path

from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup, find_packages

long_description = ""
readme = Path("./README.md")
if readme.is_file():
    with open(readme, "r", encoding="utf-8") as fh:
        long_description = fh.read()

__version__ = "0.0.2"

ext_modules = [
    Pybind11Extension(
        "_subsetsum",
        ["src/main.cpp"],
        define_macros=[("VERSION_INFO", __version__)],
    ),
]

setup(
    name="subsetsum",
    version=__version__,
    author="Trevor Phillips",
    author_email="trevphil3@gmail.com",
    url="https://github.com/trevphil/subsetsum",
    description="A Python module for finding all solutions to the SUBSET-SUM problem",
    long_description=long_description,
    long_description_content_type="text/markdown",
    package_dir={"": "src"},
    packages=find_packages(where="src"),
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.6",
)
