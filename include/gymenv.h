#include <omnetpp.h>

#include "container.h"
#include "spaces.h"

#ifndef gym_env_env
#define gym_env_env

class PynetppEnv {
   private:
    omnetpp::cSimulation *_omnet_sim;
    bool game_over;

   public:
    PynetppEnv(omnetpp::cSimulation *omnet_sim)
        : _omnet_sim(omnet_sim), game_over(false){};
    // virtual ~PynetppEnv();

    PynetppSpace *get_observation_space();
    PynetppSpace *get_action_space();

    // TODO: this should return a pointer
    PynetppContainer &get_observation();
    void execute_action(PynetppContainer &action);
    float get_reward();
    bool get_game_over() { return game_over; }
    void set_game_over(bool go) { game_over = go; }
};
#endif