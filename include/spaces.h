#include <cstdint>
#include <string>
#include <vector>

#include "dtypes.h"

#ifndef gym_env_spaces
#define gym_env_spaces
class PynetppSpace {
   public:
    PynetppSpace(){};
    virtual std::string get_space_type() const = 0;
    virtual ~PynetppSpace() {}
};

class PynetppDiscreteSpace : public PynetppSpace {
   public:
    PynetppDiscreteSpace();
    PynetppDiscreteSpace(uint32_t n);
    uint32_t get_n();
    inline std::string get_space_type() const override { return "discrete"; }

   private:
    uint32_t space_n;
};

class PynetppBoxSpace : public PynetppSpace {
   public:
    PynetppBoxSpace();
    PynetppBoxSpace(float low, float high, std::vector<uint32_t> shape,
                    PynetppDType dtype);
    // PynetppBoxSpace(std::vector<float> low, std::vector<float> high,
    //                 std::vector<uint32_t> shape, PynetppDType dtype);
    // virtual ~PynetppBoxSpace();

    float get_low();
    float get_high();
    std::vector<uint32_t> get_shape();
    inline std::string get_space_type() const override {
        return "box_" + get_dtype_string(space_dtype);
    }

   private:
    float space_low;
    float space_high;
    std::vector<uint32_t> space_shape;
    PynetppDType space_dtype;
    // std::vector<float> space_low_vect;
    // std::vector<float> space_high_vect;
};
#endif