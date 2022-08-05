#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <gymenv.h>

void bind_gymenv(pybind11::module_ &m) {
    pybind11::class_<OpenGymEnv>(
        m,
        "OpenGymEnv"
    )
        .def("get_observation_space", &OpenGymEnv::get_observation_space, pybind11::return_value_policy::reference)
        .def("get_action_space", &OpenGymEnv::get_action_space, pybind11::return_value_policy::reference)
        .def("get_observation", &OpenGymEnv::get_observation, pybind11::return_value_policy::take_ownership)
        .def("execute_action", &OpenGymEnv::execute_action)
        .def("get_reward", &OpenGymEnv::get_reward)
        .def("get_game_over", &OpenGymEnv::get_game_over)
        .def("set_game_over", &OpenGymEnv::set_game_over);
}