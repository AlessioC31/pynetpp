#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <interface.h>

void bind_interface(pybind11::module_ &m) {
    pybind11::class_<OpenGymInterface>(
        m,
        "OpenGymInterface"
    )
        .def(pybind11::init<>())
        .def("startup", &OpenGymInterface::startup)
        .def("execute_step", &OpenGymInterface::execute_step)
        .def("reset", &OpenGymInterface::reset)
        .def("stop", &OpenGymInterface::stop)
        .def("get_env", &OpenGymInterface::get_env);
}