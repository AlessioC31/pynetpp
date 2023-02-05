#include <omnetpp.h>

#include <memory>

#include "container.h"
#include "omnetpp/csimulation.h"
#include "spaces.h"

#ifndef gym_env_env
#define gym_env_env

class PynetppEnv {
   private:
    // PynetppEnv doesn't manage this pointer
    omnetpp::cSimulation *_omnet_sim;
    bool game_over;

   public:
    PynetppEnv() : game_over(false){};
    PynetppEnv(omnetpp::cSimulation *omnet_sim)
        : _omnet_sim(omnet_sim), game_over(false){};
    // virtual ~PynetppEnv();

    std::unique_ptr<PynetppSpace> get_observation_space();
    std::unique_ptr<PynetppSpace> get_action_space();

    // TODO: this should return a pointer
    std::unique_ptr<PynetppContainer> get_observation();
    void execute_action(PynetppContainer &action);
    float get_reward();
    bool get_game_over() { return game_over; }
    void set_game_over(bool go) { game_over = go; }
    void set_omnet_sim(omnetpp::cSimulation *omnet_sim) {
        _omnet_sim = omnet_sim;
    }
};
#endif