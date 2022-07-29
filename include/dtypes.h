#include <cstdint>

#ifndef gym_env_dtypes
#define gym_env_dtypes
enum OpenGymDType {
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
OpenGymDType get_dtype() {
    // TODO: should throw?
    return FLOAT;
}

template <> OpenGymDType get_dtype<int8_t> ();
template <> OpenGymDType get_dtype<int16_t> ();
template <> OpenGymDType get_dtype<int32_t> ();
template <> OpenGymDType get_dtype<int64_t> ();
template <> OpenGymDType get_dtype<uint8_t> ();
template <> OpenGymDType get_dtype<uint16_t> ();
template <> OpenGymDType get_dtype<uint32_t> ();
template <> OpenGymDType get_dtype<uint64_t> ();
template <> OpenGymDType get_dtype<float> ();
template <> OpenGymDType get_dtype<double> ();
#endif