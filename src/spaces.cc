#include "spaces.h"

#include <cstdint>
#include <vector>

#include "dtypes.h"

PynetppDiscreteSpace::PynetppDiscreteSpace() : space_n(0){};
PynetppDiscreteSpace::PynetppDiscreteSpace(uint32_t n) : space_n(n){};

uint32_t PynetppDiscreteSpace::get_n() { return space_n; }

PynetppBoxSpace::PynetppBoxSpace() {}
PynetppBoxSpace::PynetppBoxSpace(float low, float high,
                                 std::vector<uint32_t> shape,
                                 PynetppDType dtype)
    : space_low(low),
      space_high(high),
      space_shape(shape),
      space_dtype(dtype) {}
PynetppBoxSpace::PynetppBoxSpace(std::vector<float> low,
                                 std::vector<float> high,
                                 std::vector<uint32_t> shape,
                                 PynetppDType dtype)
    : space_low(0),
      space_high(0),
      space_shape(shape),
      space_dtype(dtype),
      space_low_vect(low),
      space_high_vect(high) {}

float PynetppBoxSpace::get_low() { return space_low; }

float PynetppBoxSpace::get_high() { return space_high; }

std::vector<uint32_t> PynetppBoxSpace::get_shape() { return space_shape; }