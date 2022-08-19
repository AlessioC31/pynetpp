#include <gymenv.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

void bind_gymenv(pybind11::module_& m) {
    pybind11::class_<PynetppEnv>(m, "PynetppEnv")
        .def("get_observation_space", &PynetppEnv::get_observation_space,
             pybind11::return_value_policy::take_ownership)
        .def("get_action_space", &PynetppEnv::get_action_space,
             pybind11::return_value_policy::take_ownership)
        .def("get_observation", &PynetppEnv::get_observation,
             pybind11::return_value_policy::take_ownership)
        .def("execute_action", &PynetppEnv::execute_action)
        .def("get_reward", &PynetppEnv::get_reward)
        .def("get_game_over", &PynetppEnv::get_game_over)
        .def("set_game_over", &PynetppEnv::set_game_over);
}