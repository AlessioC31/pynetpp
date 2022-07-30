#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <container.h>

void bind_container(pybind11::module_ &m) {
    pybind11::class_<OpenGymContainer>(
        m,
        "OpenGymContainer"
    );

    pybind11::class_<OpenGymDiscreteContainer, OpenGymContainer>(
        m,
        "OpenGymDiscreteContainer"
    )
        .def(pybind11::init<>())
        .def(pybind11::init<const uint32_t>())
        .def("set_value", &OpenGymDiscreteContainer::set_value)
        .def("get_value", &OpenGymDiscreteContainer::get_value);

    pybind11::class_<OpenGymBoxContainer<float>, OpenGymContainer>(
        m,
        "OpenGymBoxContainer"
    )
        .def(pybind11::init<>())
        .def(pybind11::init<std::vector<uint32_t>>())
        .def("add_value", &OpenGymBoxContainer<float>::add_value)
        .def("get_value", &OpenGymBoxContainer<float>::get_value)
        .def("set_data", &OpenGymBoxContainer<float>::set_data)
        .def("get_data", &OpenGymBoxContainer<float>::get_data)
        .def("get_shape", &OpenGymBoxContainer<float>::get_shape);
        // .def("get_low", &OpenGymBoxSpace::get_low)
        // .def("get_high", &OpenGymBoxSpace::get_high)
        // .def("get_shape", &OpenGymBoxSpace::get_shape);
}