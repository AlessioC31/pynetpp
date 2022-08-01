#include <omnetpp.h>
#include <string.h>
#include <interface.h>
#include <gymenv.h>
#include "server.h"
#include "loadbalancer.h"
#include <dtypes.h>

using namespace omnetpp;

class EmptyConfig : public cConfiguration {
    protected:
        class NullKeyValue : public KeyValue {
            public:
                virtual const char* getKey() const override {return nullptr;}
                virtual const char* getValue() const override {return nullptr;}
                virtual const char* getBaseDirectory() const override {return nullptr;}
        };
        NullKeyValue nullKeyValue;

        protected:
            virtual const char* substituteVariables(const char* value) const override {return value;}

        public:
            virtual const char* getConfigValue(const char* key) const override {return nullptr;}
            virtual const KeyValue& getConfigEntry(const char* key) const override {return nullKeyValue;}
            virtual const char* getPerObjectConfigValue(const char* objectFullPath, const char* keySuffix) const override {return nullptr;}
            virtual const KeyValue& getPerObjectConfigEntry(const char* objectFullPath, const char* keySuffix) const override {return nullKeyValue;}
};

class MinimalEnv : public cNullEnvir {
    public:
        MinimalEnv(int ac, char** av, cConfiguration* c) : cNullEnvir(ac, av, c) {}

        virtual void readParameter(cPar* par) override {
            if (par->containsValue())
                par->acceptDefault();
            else
                throw cRuntimeError("no value for parameter %s", par->getFullPath().c_str());
        }

        virtual void sputn(const char* s, int n) {
            (void) ::fwrite(s, 1, n, stdout);
        }
};

OpenGymSpace& OpenGymEnv::get_observation_space() {
    OpenGymBoxSpace* space = new OpenGymBoxSpace(0, 10000, std::vector<uint32_t> {3}, FLOAT);

    return *space;
}

OpenGymSpace& OpenGymEnv::get_action_space() {
    OpenGymDiscreteSpace* space = new OpenGymDiscreteSpace(4);

    return *space;
}

OpenGymContainer& OpenGymEnv::get_observation() {
    OpenGymBoxContainer<float>& to_ret = *new OpenGymBoxContainer<float>(std::vector<uint32_t> {3});

    for (int i = 0; i < 4; i ++) {
        std::string module_name = "Loadbalancernet.server[" + std::to_string(i) + "]";
        loadbalancing::Server* s = (loadbalancing::Server*) _omnet_sim->getModuleByPath(module_name.c_str());
        to_ret.add_value(s->get_load());
    }

    return to_ret;
}

void OpenGymEnv::execute_action(OpenGymContainer& action) {
    OpenGymDiscreteContainer& discrete_action = (OpenGymDiscreteContainer&) action;

    loadbalancing::Loadbalancer* l = (loadbalancing::Loadbalancer*) _omnet_sim->getModuleByPath("Loadbalancernet.loadbalancer");
    l->set_server_idx(discrete_action.get_value());
}

float OpenGymEnv::get_reward() {
    return 0;
}

OpenGymInterface::OpenGymInterface() {
    _dummy = new cStaticFlag();
    cEnvir* omnetpp_env = new MinimalEnv(0, NULL, new EmptyConfig());
    cSimulation* sim = new cSimulation("simulation", omnetpp_env);

    OpenGymEnv* gym_env = new OpenGymEnv(sim);
    _env = gym_env;
    _sim = sim;
}

void OpenGymInterface::startup() {
    CodeFragments::executeAll(CodeFragments::STARTUP);
    SimTime::setScaleExp(-12);
    cSimulation::setActiveSimulation(_sim);
    cSimulation::loadNedSourceFolder("model");
    cSimulation::doneLoadingNedFiles();

    cModuleType* networkType = cModuleType::find("Loadbalancernet");

    if (networkType == nullptr) {
        //TODO: throw something
        printf("network not found \n");
    }

    _sim->setupNetwork(networkType);
    _sim->setSimulationTimeLimit(1000);

    _sim->callInitialize();
}

void OpenGymInterface::execute_step() {
    try {
        for (int i = 0; i < 5; i ++) {
            cEvent* event =  _sim->takeNextEvent();

            if (event) {
                _sim->executeEvent(event);
            } else {
                _env->set_game_over(true);
                break;
            }
        }
    } catch (cTerminationException& e) {
        _env->set_game_over(true);
    }

}

void OpenGymInterface::reset() {
     _sim->callFinish();
    _sim->deleteNetwork();
    _sim->setActiveSimulation(nullptr);
    delete _sim;
    
    cEnvir* omnetpp_env = new MinimalEnv(0, NULL, new EmptyConfig());
    cSimulation* sim = new cSimulation("simulation", omnetpp_env);

    OpenGymEnv* gym_env = new OpenGymEnv(sim);
    _env = gym_env;
    _sim = sim;

    cSimulation::setActiveSimulation(_sim);
    cModuleType* networkType = cModuleType::find("Loadbalancernet");

    _sim->setupNetwork(networkType);
    _sim->setSimulationTimeLimit(1000);

    _sim->callInitialize();
}

void OpenGymInterface::stop() {
    _sim->callFinish();
    _sim->deleteNetwork();
    _sim->setActiveSimulation(nullptr);
    delete _sim;

    CodeFragments::executeAll(CodeFragments::SHUTDOWN);
}

int main() {
    OpenGymInterface* interface = new OpenGymInterface();
    interface->startup();
    for (int i = 0; i < 5; i ++)
        interface->execute_step();
    
    // interface->startup();
    // interface->stop();
    // interface->execute_step();

    OpenGymDiscreteContainer* act_container = new OpenGymDiscreteContainer(4);
    act_container->set_value(1);

    interface->get_env().execute_action(*act_container);
    for (int i = 0; i < 5; i ++)
        interface->execute_step();

    OpenGymBoxContainer<float>& obs = (OpenGymBoxContainer<float>&) interface->get_env().get_observation();
    std::vector<float> v = obs.get_data();

    for (float el : v) {
        std::cout<<el<<endl;
    }

    interface->stop();

    return 0;
}