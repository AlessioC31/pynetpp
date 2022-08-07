#include <cstdint>

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

template<typename T>
constexpr PynetppDType get_dtype() {
    // TODO: should throw?
    return FLOAT;
}

template <> constexpr PynetppDType get_dtype<int8_t> () { return INT8; }
template <> constexpr PynetppDType get_dtype<int16_t> () { return INT16; }
template <> constexpr PynetppDType get_dtype<int32_t> ()  { return INT32; }
template <> constexpr PynetppDType get_dtype<int64_t> () { return INT64; }
template <> constexpr PynetppDType get_dtype<uint8_t> () { return UINT8; }
template <> constexpr PynetppDType get_dtype<uint16_t> () { return UINT16; }
template <> constexpr PynetppDType get_dtype<uint32_t> () { return UINT32; }
template <> constexpr PynetppDType get_dtype<uint64_t> () { return UINT64; }
template <> constexpr PynetppDType get_dtype<float> () { return FLOAT; }
template <> constexpr PynetppDType get_dtype<double> () { return DOUBLE; }
#endif