#include <dtypes.h>
#include <gymenv.h>
#include <interface.h>
#include <omnetpp.h>
#include <string.h>

#include "loadbalancer.h"
#include "server.h"

using namespace omnetpp;

class EmptyConfig : public cConfiguration {
   protected:
    class NullKeyValue : public KeyValue {
       public:
        virtual const char* getKey() const override { return nullptr; }
        virtual const char* getValue() const override { return nullptr; }
        virtual const char* getBaseDirectory() const override {
            return nullptr;
        }
    };
    NullKeyValue nullKeyValue;

   protected:
    virtual const char* substituteVariables(const char* value) const override {
        return value;
    }

   public:
    virtual const char* getConfigValue(const char* key) const override {
        return nullptr;
    }
    virtual const KeyValue& getConfigEntry(const char* key) const override {
        return nullKeyValue;
    }
    virtual const char* getPerObjectConfigValue(
        const char* objectFullPath, const char* keySuffix) const override {
        return nullptr;
    }
    virtual const KeyValue& getPerObjectConfigEntry(
        const char* objectFullPath, const char* keySuffix) const override {
        return nullKeyValue;
    }
};

class MinimalEnv : public cNullEnvir {
   public:
    MinimalEnv(int ac, char** av, cConfiguration* c) : cNullEnvir(ac, av, c) {}

    virtual void readParameter(cPar* par) override {
        if (par->containsValue())
            par->acceptDefault();
        else
            throw cRuntimeError("no value for parameter %s",
                                par->getFullPath().c_str());
    }

    virtual void sputn(const char* s, int n) {
        (void)::fwrite(s, 1, n, stdout);
    }
};

PynetppSpace* PynetppEnv::get_observation_space() {
    auto* space =
        new PynetppBoxSpace(0, 10000, std::vector<uint32_t>{4}, FLOAT);

    return space;
}

PynetppSpace* PynetppEnv::get_action_space() {
    auto* space = new PynetppDiscreteSpace(4);

    return space;
}

PynetppContainer& PynetppEnv::get_observation() {
    PynetppBoxContainer<float>* to_ret = new PynetppBoxContainer<float>({
        4,
    });

    for (unsigned i = 0; i < 4; i++) {
        std::string module_name =
            "Loadbalancernet.server[" + std::to_string(i) + "]";
        loadbalancing::Server* s =
            (loadbalancing::Server*)_omnet_sim->getModuleByPath(
                module_name.c_str());

        (*to_ret)({i}) = s->get_load();
    }

    return *to_ret;
}

void PynetppEnv::execute_action(PynetppContainer& action) {
    PynetppDiscreteContainer& discrete_action =
        (PynetppDiscreteContainer&)action;

    loadbalancing::Loadbalancer* l =
        (loadbalancing::Loadbalancer*)_omnet_sim->getModuleByPath(
            "Loadbalancernet.loadbalancer");
    l->set_server_idx(discrete_action.get_value());
}

float PynetppEnv::get_reward() { return 0; }

PynetppInterface::PynetppInterface() {
    _dummy = new cStaticFlag();
    cEnvir* omnetpp_env = new MinimalEnv(0, NULL, new EmptyConfig());
    cSimulation* sim = new cSimulation("simulation", omnetpp_env);

    PynetppEnv* gym_env = new PynetppEnv(sim);
    _env = gym_env;
    _sim = sim;
}

// void PynetppInterface::startup() {
//     CodeFragments::executeAll(CodeFragments::STARTUP);
//     SimTime::setScaleExp(-12);
//     cSimulation::setActiveSimulation(_sim);
//     cSimulation::loadNedSourceFolder("model");
//     cSimulation::doneLoadingNedFiles();

//     cModuleType* networkType = cModuleType::find("Loadbalancernet");

//     if (networkType == nullptr) {
//         // TODO: throw something
//         printf("network not found \n");
//     }

//     _sim->setupNetwork(networkType);
//     _sim->setSimulationTimeLimit(100);

//     _sim->callInitialize();
// }

void PynetppInterface::execute_step(int steps) {
    // try {
    for (int i = 0; i < steps; i++) {
        cEvent* event = _sim->takeNextEvent();

        if (event) {
            _sim->executeEvent(event);
        } else {
            _env->set_game_over(true);
            break;
        }
    }
    // } catch (cTerminationException& e) {
    //     _env->set_game_over(true);
    // }
}

void PynetppInterface::reset() {
    _sim->callFinish();
    _sim->deleteNetwork();
    _sim->setActiveSimulation(nullptr);
    delete _sim;

    cEnvir* omnetpp_env = new MinimalEnv(0, NULL, new EmptyConfig());
    cSimulation* sim = new cSimulation("simulation", omnetpp_env);

    PynetppEnv* gym_env = new PynetppEnv(sim);
    _env = gym_env;
    _sim = sim;

    cSimulation::setActiveSimulation(_sim);
    cModuleType* networkType = cModuleType::find("Loadbalancernet");

    _sim->setupNetwork(networkType);
    _sim->setSimulationTimeLimit(100);

    _sim->callInitialize();
}

void PynetppInterface::stop() {
    _sim->callFinish();
    _sim->deleteNetwork();
    _sim->setActiveSimulation(nullptr);
    delete _sim;

    CodeFragments::executeAll(CodeFragments::SHUTDOWN);
}

// int main() {
//     PynetppInterface* interface = new PynetppInterface();
//     interface->startup();
//     for (int i = 0; i < 5; i ++)
//         interface->execute_step();

//     // interface->startup();
//     // interface->stop();
//     // interface->execute_step();

//     PynetppDiscreteContainer* act_container = new
//     PynetppDiscreteContainer(4); act_container->set_value(1);

//     interface->get_env().execute_action(*act_container);
//     for (int i = 0; i < 5; i ++)
//         interface->execute_step();

//     PynetppBoxContainer<float>& obs = (PynetppBoxContainer<float>&)
//     interface->get_env().get_observation(); std::vector<float> v =
//     obs.get_data();

//     for (float el : v) {
//         std::cout<<el<<endl;
//     }

//     interface->stop();

//     return 0;
// }