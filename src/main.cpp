#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "subsetsum.cpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(_subsetsum, m) {
    py::class_<subsetsum::Solver>(m, "Solver")
        .def(py::init<const std::vector<int>&, int>())
        .def("hasSolution", &subsetsum::Solver::hasSolution)
        .def("initSolutionIterator", &subsetsum::Solver::initSolutionIterator)
        .def("getNextSolution", &subsetsum::Solver::getNextSolution);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
