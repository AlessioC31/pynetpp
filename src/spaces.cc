#include "spaces.h"
#include "dtypes.h"
#include <vector>

OpenGymDiscreteSpace::OpenGymDiscreteSpace() {};
OpenGymDiscreteSpace::OpenGymDiscreteSpace(int n) : space_n(n) { };

int OpenGymDiscreteSpace::get_n() {
    return space_n;
}

OpenGymBoxSpace::OpenGymBoxSpace() {}
OpenGymBoxSpace::OpenGymBoxSpace(float low, float high, std::vector<uint32_t> shape, OpenGymDType dtype):
    space_low(low), space_high(high), space_shape(shape), space_dtype(dtype){

    }
OpenGymBoxSpace::OpenGymBoxSpace(std::vector<float> low, std::vector<float> high, std::vector<uint32_t> shape, OpenGymDType dtype):
    space_low(0), space_high(0), space_shape(shape), space_dtype(dtype), space_low_vect(low), space_high_vect(high) {

    }

float OpenGymBoxSpace::get_low() {
    return space_low;
}

float OpenGymBoxSpace::get_high() {
    return space_high;
}

std::vector<uint32_t> OpenGymBoxSpace::get_shape() {
    return space_shape;
}