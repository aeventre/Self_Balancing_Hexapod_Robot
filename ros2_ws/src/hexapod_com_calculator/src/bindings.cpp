#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "com_calculator.cpp"

namespace py = pybind11;

PYBIND11_MODULE(com_calculator, m) {
    m.doc() = "Center of Mass Calculator Module";
    m.def("calculate_com", &calculate_com, "Calculate the center of mass",
          py::arg("masses"), py::arg("positions"));
}
