#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "container.h"
#include "dtypes.h"

#ifndef gym_env_spaces
#define gym_env_spaces
class PynetppSpace {
   public:
    PynetppSpace() = default;
    virtual std::string get_space_type() const = 0;
    // virtual PynetppContainer* get_container() const = 0;
    virtual ~PynetppSpace() = default;
};

class PynetppDiscreteSpace : public PynetppSpace {
   public:
    PynetppDiscreteSpace() : space_n(0) {}
    PynetppDiscreteSpace(uint32_t n) : space_n(n) {}
    inline uint32_t get_n() { return space_n; }
    inline std::string get_space_type() const override { return "discrete"; }

    // PynetppDiscreteContainer* get_container() const override {
    //     auto c = new PynetppDiscreteContainer(space_n);

    //     return c;
    // }

   private:
    uint32_t space_n;
};

// TODO: maybe use template instead PynetppDType to manage types of space?
class PynetppBoxSpace : public PynetppSpace {
   public:
    PynetppBoxSpace() {}
    PynetppBoxSpace(float low, float high, std::vector<uint32_t> shape,
                    PynetppDType dtype)
        : space_low(low),
          space_high(high),
          space_shape(shape),
          space_dtype(dtype) {}
    // PynetppBoxSpace(std::vector<float> low, std::vector<float> high,
    //                 std::vector<uint32_t> shape, PynetppDType dtype);
    // virtual ~PynetppBoxSpace();

    inline float get_low() { return space_low; }
    inline float get_high() { return space_high; }
    inline std::vector<uint32_t> get_shape() { return space_shape; }
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