#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "subsetsum.cpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(subsetsum, m) {
    py::class_<subset_sum::Solver>(m, "Solver")
        .def(py::init<const std::vector<int>&, int>())
        .def("hasSolution", &subset_sum::Solver::hasSolution)
        .def("initSolutionIterator", &subset_sum::Solver::initSolutionIterator)
        .def("getNextSolution", &subset_sum::Solver::getNextSolution);

    m.def("add", &add);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
