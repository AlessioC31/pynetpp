#include <omnetpp.h>

#include "container.h"
#include "spaces.h"

#ifndef gym_env_env
#define gym_env_env

class OpenGymEnv {
    private:
        omnetpp::cSimulation* _omnet_sim;
        bool game_over;

    public:
        OpenGymEnv(omnetpp::cSimulation* omnet_sim) : _omnet_sim(omnet_sim) {}; 
        // virtual ~OpenGymEnv();

        OpenGymSpace& get_observation_space();
        OpenGymSpace& get_action_space();
        OpenGymContainer& get_observation();
        void execute_action(OpenGymContainer& action);
        float get_reward();
        bool get_game_over() { return game_over; }
        void set_game_over(bool go) { game_over = go; }
};
#endif