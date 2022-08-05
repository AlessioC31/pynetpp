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
PynetppDType get_dtype() {
    // TODO: should throw?
    return FLOAT;
}

template <> PynetppDType get_dtype<int8_t> ();
template <> PynetppDType get_dtype<int16_t> ();
template <> PynetppDType get_dtype<int32_t> ();
template <> PynetppDType get_dtype<int64_t> ();
template <> PynetppDType get_dtype<uint8_t> ();
template <> PynetppDType get_dtype<uint16_t> ();
template <> PynetppDType get_dtype<uint32_t> ();
template <> PynetppDType get_dtype<uint64_t> ();
template <> PynetppDType get_dtype<float> ();
template <> PynetppDType get_dtype<double> ();
#endif