#include <vector>
#include <cstdint>
#include "dtypes.h"

#ifndef gym_env_spaces
#define gym_env_spaces
class OpenGymSpace {
    public:
        OpenGymSpace() {};
        // virtual ~OpenGymSpace();
};

class OpenGymDiscreteSpace : public OpenGymSpace {
    public:
        OpenGymDiscreteSpace();
        OpenGymDiscreteSpace(int n);
        int get_n();

    private:
        int space_n;
};

class OpenGymBoxSpace : public OpenGymSpace {
    public:
        OpenGymBoxSpace();
        OpenGymBoxSpace(float low, float high, std::vector<uint32_t> shape, OpenGymDType dtype);
        OpenGymBoxSpace(std::vector<float> low, std::vector<float> high, std::vector<uint32_t> shape, OpenGymDType dtype);
        // virtual ~OpenGymBoxSpace();

        float get_low();
        float get_high();
        std::vector<uint32_t> get_shape();

    private:
        float space_low;
        float space_high;
        std::vector<uint32_t> space_shape;
        OpenGymDType space_dtype;
        std::vector<float> space_low_vect;
        std::vector<float> space_high_vect;
};
#endif