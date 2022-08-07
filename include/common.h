// https://stackoverflow.com/questions/1055452/c-get-name-of-type-in-template

#include <string>

#ifndef pynetpp_common
#define pynetpp_common

template <typename T>
struct TypeTraits;

#define REGISTER_TYPE(X)               \
    template <>                        \
    struct TypeTraits<X> {             \
        static const std::string name; \
    };                                 \
    inline const std::string TypeTraits<X>::name = #X

REGISTER_TYPE(int8_t);
REGISTER_TYPE(int16_t);
REGISTER_TYPE(int32_t);
REGISTER_TYPE(int64_t);
REGISTER_TYPE(uint8_t);
REGISTER_TYPE(uint16_t);
REGISTER_TYPE(uint32_t);
REGISTER_TYPE(uint64_t);
REGISTER_TYPE(float);
REGISTER_TYPE(double);

#endif