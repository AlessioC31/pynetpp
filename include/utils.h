#include <envir/envirbase.h>
#include <envir/xmldoccache.h>
#include <omnetpp.h>

#ifndef gym_env_utils
#define gym_env_utils
class MinimalEnv : public omnetpp::envir::EnvirBase {
   public:
    MinimalEnv(omnetpp::cConfiguration *c) : omnetpp::envir::EnvirBase() {
        cfg = static_cast<omnetpp::cConfigurationEx *>(c);
        opt = createOptions();
        args = new omnetpp::envir::ArgList();
    }
    bool setup() override {
        readOptions();
        cfg->activateConfig("General", 0);
        readPerRunOptions();
        xmlCache = new omnetpp::envir::XMLDocCache();
        return true;
        // return ::envir::EnvirBase::setup();
    }

    virtual ~MinimalEnv(){};
    void printUISpecificHelp() override {}
    void askParameter(omnetpp::cPar *par, bool unassigned) override {}
    virtual unsigned getExtraStackForEnvir() const override { return 0; }
    bool isGUI() const override { return false; }
    bool isExpressMode() const override { return false; }
    void alert(const char *msg) override { ::printf("\n<!> %s\n\n", msg); }
    std::string gets(const char *prompt,
                     const char *defaultReply = nullptr) override {
        unsupported();
        return nullptr;
    }
    bool askYesNo(const char *prompt) override {
        unsupported();
        return false;
    }
    void getImageSize(const char *imageName, double &outWidth,
                      double &outHeight) override {
        unsupported();
    }
    void getTextExtent(const omnetpp::cFigure::Font &font, const char *text,
                       double &outWidth, double &outHeight,
                       double &outAscent) override {
        unsupported();
    }
    void appendToImagePath(const char *directory) override { unsupported(); }
    void loadImage(const char *fileName,
                   const char *imageName = nullptr) override {
        unsupported();
    }
    omnetpp::cFigure::Rectangle getSubmoduleBounds(
        const omnetpp::cModule *submodule) override {
        return omnetpp::cFigure::Rectangle(NAN, NAN, NAN, NAN);
    }
    std::vector<omnetpp::cFigure::Point> getConnectionLine(
        const omnetpp::cGate *sourceGate) override {
        return {};
    }
    double getZoomLevel(const omnetpp::cModule *module) override { return NAN; }
    double getAnimationTime() const override { return 0; }
    double getAnimationSpeed() const override { return 0; }
    double getRemainingAnimationHoldTime() const override { return 0; }
    void pausePoint() override {}
    void doRun() override {}

   protected:
    void unsupported() const {
        throw omnetpp::cRuntimeError("MinimalEnv: Unsupported method called");
    }
};
#endif