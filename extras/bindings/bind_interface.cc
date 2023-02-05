#include <interface.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "pybind11/detail/common.h"

void bind_interface(pybind11::module_ &m) {
    pybind11::class_<PynetppInterface>(m, "PynetppInterface")
        .def(pybind11::init<std::string, std::string, std::vector<std::string>,
                            uint64_t, int64_t>())
        .def("startup", &PynetppInterface::startup)
        .def("execute_step", &PynetppInterface::execute_step)
        .def("reset", &PynetppInterface::reset)
        .def("stop", &PynetppInterface::stop)
        .def("get_env", &PynetppInterface::get_env,
             pybind11::return_value_policy::reference);
}