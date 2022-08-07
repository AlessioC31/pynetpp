#include <cstdint>
#include <string>

#ifndef gym_env_dtypes
#define gym_env_dtypes
enum PynetppDType {
    INT8,
    INT16,
    INT32,
    INT64,
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    FLOAT,
    DOUBLE
};

template <typename T>
constexpr PynetppDType get_dtype() {
    // TODO: should throw?
    return FLOAT;
}

inline std::string get_dtype_string(PynetppDType dtype) {
    switch (dtype) {
        case INT8:
            return "int8_t";
        case INT16:
            return "int16_t";
        case INT32:
            return "int32_t";
        case INT64:
            return "int64_t";
        case UINT8:
            return "uint8_t";
        case UINT16:
            return "uint16_t";
        case UINT32:
            return "uint32_t";
        case UINT64:
            return "uint64_t";
        case FLOAT:
            return "float";
        case DOUBLE:
            return "double";
        default:
            return "float";  // needed to make compiler happy
    }
}

template <>
constexpr PynetppDType get_dtype<int8_t>() {
    return INT8;
}
template <>
constexpr PynetppDType get_dtype<int16_t>() {
    return INT16;
}
template <>
constexpr PynetppDType get_dtype<int32_t>() {
    return INT32;
}
template <>
constexpr PynetppDType get_dtype<int64_t>() {
    return INT64;
}
template <>
constexpr PynetppDType get_dtype<uint8_t>() {
    return UINT8;
}
template <>
constexpr PynetppDType get_dtype<uint16_t>() {
    return UINT16;
}
template <>
constexpr PynetppDType get_dtype<uint32_t>() {
    return UINT32;
}
template <>
constexpr PynetppDType get_dtype<uint64_t>() {
    return UINT64;
}
template <>
constexpr PynetppDType get_dtype<float>() {
    return FLOAT;
}
template <>
constexpr PynetppDType get_dtype<double>() {
    return DOUBLE;
}
#endif