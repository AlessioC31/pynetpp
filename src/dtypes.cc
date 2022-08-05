#include "dtypes.h"
#include <cstdint>

template <> PynetppDType get_dtype<int8_t> () { return INT8; }
template <> PynetppDType get_dtype<int16_t> () { return INT16; }
template <> PynetppDType get_dtype<int32_t> ()  { return INT32; }
template <> PynetppDType get_dtype<int64_t> () { return INT64; }
template <> PynetppDType get_dtype<uint8_t> () { return UINT8; }
template <> PynetppDType get_dtype<uint16_t> () { return UINT16; }
template <> PynetppDType get_dtype<uint32_t> () { return UINT32; }
template <> PynetppDType get_dtype<uint64_t> () { return UINT64; }
template <> PynetppDType get_dtype<float> () { return FLOAT; }
template <> PynetppDType get_dtype<double> () { return DOUBLE; }