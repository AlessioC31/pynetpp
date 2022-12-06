#include <omnetpp.h>

#include "container.h"
#include "gymenv.h"

#ifndef gym_env_interface
#define gym_env_interface
class PynetppInterface {
   public:
    PynetppInterface();
    // PynetppInterface::PynetppInterface(omnetpp::cSimulation* sim, PynetppEnv*
    // env) : _sim(sim), _env(env) {};
    void startup();
    void execute_step(int steps);
    void reset();
    void stop();

    PynetppEnv &get_env() { return *_env; }

   private:
    omnetpp::cSimulation *_sim;
    PynetppEnv *_env;
    omnetpp::cStaticFlag *_dummy;
};
#endif