#include <omnetpp.h>

#include "gymenv.h"

#ifndef gym_env_interface
#define gym_env_interface
class OpenGymInterface {
    public:
        OpenGymInterface();
        // OpenGymInterface::OpenGymInterface(omnetpp::cSimulation* sim, OpenGymEnv* env) : _sim(sim), _env(env) {};
        void startup();
        void execute_step();
        void stop();

        OpenGymEnv& get_env() { return *_env; }

    private:
        omnetpp::cSimulation* _sim;
        OpenGymEnv* _env;
        omnetpp::cStaticFlag* _dummy;
};  
#endif