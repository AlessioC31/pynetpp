#include "dtypes.h"
#include <cstdint>

template <> OpenGymDType get_dtype<int8_t> () { return INT8; }
template <> OpenGymDType get_dtype<int16_t> () { return INT16; }
template <> OpenGymDType get_dtype<int32_t> ()  { return INT32; }
template <> OpenGymDType get_dtype<int64_t> () { return INT64; }
template <> OpenGymDType get_dtype<uint8_t> () { return UINT8; }
template <> OpenGymDType get_dtype<uint16_t> () { return UINT16; }
template <> OpenGymDType get_dtype<uint32_t> () { return UINT32; }
template <> OpenGymDType get_dtype<uint64_t> () { return UINT64; }
template <> OpenGymDType get_dtype<float> () { return FLOAT; }
template <> OpenGymDType get_dtype<double> () { return DOUBLE; }