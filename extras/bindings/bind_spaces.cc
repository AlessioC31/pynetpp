#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <spaces.h>
#include <cstdint>
#include <dtypes.h>

void bind_spaces(pybind11::module_ &m) {
    pybind11::class_<OpenGymSpace>(
        m,
        "OpenGymSpace"
    )
        .def("get_space_type", &OpenGymSpace::get_space_type);

    pybind11::class_<OpenGymDiscreteSpace, OpenGymSpace>(
        m,
        "OpenGymDiscreteSpace"
    )
        .def(pybind11::init<>())
        .def(pybind11::init<const uint32_t>())
        .def("get_space_type", &OpenGymDiscreteSpace::get_space_type)
        .def("get_n", &OpenGymDiscreteSpace::get_n);

    pybind11::class_<OpenGymBoxSpace, OpenGymSpace>(
        m,
        "OpenGymBoxSpace"
    )
        .def(pybind11::init<>())
        .def(pybind11::init<float, float, std::vector<uint32_t>, OpenGymDType>())
        .def(pybind11::init<std::vector<float>, std::vector<float>, std::vector<uint32_t>, OpenGymDType>())
        .def("get_low", &OpenGymBoxSpace::get_low)
        .def("get_high", &OpenGymBoxSpace::get_high)
        .def("get_space_type", &OpenGymBoxSpace::get_space_type)
        .def("aaa", &OpenGymBoxSpace::aaa)
        .def("get_shape", &OpenGymBoxSpace::get_shape);
}