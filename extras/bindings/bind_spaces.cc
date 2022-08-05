#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <spaces.h>
#include <cstdint>
#include <dtypes.h>

void bind_spaces(pybind11::module_ &m) {
    pybind11::class_<PynetppSpace>(
        m,
        "PynetppSpace"
    )
        .def("get_space_type", &PynetppSpace::get_space_type);

    pybind11::class_<PynetppDiscreteSpace, PynetppSpace>(
        m,
        "PynetppDiscreteSpace"
    )
        .def(pybind11::init<>())
        .def(pybind11::init<const uint32_t>())
        .def("get_space_type", &PynetppDiscreteSpace::get_space_type)
        .def("get_n", &PynetppDiscreteSpace::get_n);

    pybind11::class_<PynetppBoxSpace, PynetppSpace>(
        m,
        "PynetppBoxSpace"
    )
        .def(pybind11::init<>())
        .def(pybind11::init<float, float, std::vector<uint32_t>, PynetppDType>())
        .def(pybind11::init<std::vector<float>, std::vector<float>, std::vector<uint32_t>, PynetppDType>())
        .def("get_low", &PynetppBoxSpace::get_low)
        .def("get_high", &PynetppBoxSpace::get_high)
        .def("get_space_type", &PynetppBoxSpace::get_space_type)
        .def("get_shape", &PynetppBoxSpace::get_shape);
}