#include <pybind11/pybind11.h>
#include <dtypes.h>

void bind_dtypes(pybind11::module_ &m) {
    pybind11::enum_<OpenGymDType>(
        m,
        "OpenGymDType"
    )
        .value("INT8", OpenGymDType::INT8)
        .value("INT16", OpenGymDType::INT16)
        .value("INT32", OpenGymDType::INT32)
        .value("INT64", OpenGymDType::INT64)
        .value("UINT8", OpenGymDType::UINT8)
        .value("UINT16", OpenGymDType::UINT16)
        .value("UINT32", OpenGymDType::UINT32)
        .value("UINT64", OpenGymDType::UINT64)
        .value("FLOAT", OpenGymDType::FLOAT)
        .value("DOUBLE", OpenGymDType::DOUBLE)
        .export_values();
}