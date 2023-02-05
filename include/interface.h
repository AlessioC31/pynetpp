#include <envir/args.h>
#include <envir/envirbase.h>
#include <envir/inifilereader.h>
#include <envir/sectionbasedconfig.h>
#include <envir/xmldoccache.h>
#include <omnetpp.h>

#include <cstdint>
#include <memory>
#include <string>

#include "container.h"
#include "gymenv.h"
#include "omnetpp/ccomponenttype.h"
#include "omnetpp/cevent.h"
#include "omnetpp/cexception.h"
#include "omnetpp/cownedobject.h"
#include "omnetpp/csimulation.h"
#include "omnetpp/onstartup.h"
#include "omnetpp/simtime.h"
#include "utils.h"

#ifndef gym_env_interface
#define gym_env_interface
class PynetppInterface {
   public:
    PynetppInterface(std::string network_name, std::string ini_file,
                     std::vector<std::string> ned_folders,
                     uint64_t time_limit = 10, int64_t scale = -12)
        : _network_name(network_name),
          _ini_file(ini_file),
          _ned_folders(ned_folders),
          _time_limit(time_limit),
          _scale(scale) {
        // Needed by omnetpp for obscure reasons
        _dummy = new omnetpp::cStaticFlag();
        _env = std::make_unique<PynetppEnv>();
        // omnetpp::SimTime::setScaleExp(_scale);
    }
    // PynetppInterface::PynetppInterface(omnetpp::cSimulation* sim, PynetppEnv*
    // env) : _sim(sim), _env(env) {};
    void startup() { setup(true); }

    void execute_step(int steps) {
        // try {
        for (uint i = 0; i < steps; i++) {
            omnetpp::cEvent *event = _sim->takeNextEvent();

            if (event) {
                _sim->executeEvent(event);
            } else {
                _env->set_game_over(true);
                break;
            }
        }
        // } catch (omnetpp::cTerminationException &e) {
        //     _env->set_game_over(true);
        // }
    }
    void reset() {
        tear_down();
        setup(false);
    }
    inline void stop() {
        tear_down();

        omnetpp::CodeFragments::executeAll(omnetpp::CodeFragments::SHUTDOWN);
    }

    PynetppEnv &get_env() { return *_env; }

   private:
    inline void tear_down() {
        _sim->callFinish();
        _sim->deleteNetwork();
        _sim->setActiveSimulation(nullptr);
        delete _sim;
    }

    void setup(bool startup) {
        auto *ifr = new omnetpp::envir::InifileReader();

        if (_ini_file.length() > 0) ifr->readFile(_ini_file.c_str());

        auto *conf = new omnetpp::envir::SectionBasedConfiguration();
        conf->setConfigurationReader(ifr);

        auto *env = new MinimalEnv(conf);
        auto *sim = new omnetpp::cSimulation("pynetppSimulation", env);

        _env->set_omnet_sim(sim);
        _sim = sim;

        if (startup) {
            omnetpp::CodeFragments::executeAll(omnetpp::CodeFragments::STARTUP);
        }

        omnetpp::cSimulation::setActiveSimulation(_sim);
        env->setup();

        if (startup) {
            for (std::string ned_folder : _ned_folders) {
                omnetpp::cSimulation::loadNedSourceFolder(ned_folder.c_str());
            }
            omnetpp::cSimulation::doneLoadingNedFiles();
        }

        omnetpp::cModuleType *networkType =
            omnetpp::cModuleType::find(_network_name.c_str());

        if (networkType == nullptr) {
            // TODO: throw something
            printf("network not found \n");
        }
        _sim->setupNetwork(networkType);
        _sim->setSimulationTimeLimit(_time_limit);
        _sim->callInitialize();
    }

    omnetpp::cSimulation *_sim;
    std::unique_ptr<PynetppEnv> _env;
    omnetpp::cStaticFlag *_dummy;
    std::string _network_name;
    std::string _ini_file;
    std::vector<std::string> _ned_folders;
    uint64_t _time_limit;
    int64_t _scale;
};
#endif