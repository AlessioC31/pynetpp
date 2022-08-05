#include <pybind11/pybind11.h>
#include <dtypes.h>

void bind_dtypes(pybind11::module_ &m) {
    pybind11::enum_<PynetppDType>(
        m,
        "PynetppDType"
    )
        .value("INT8", PynetppDType::INT8)
        .value("INT16", PynetppDType::INT16)
        .value("INT32", PynetppDType::INT32)
        .value("INT64", PynetppDType::INT64)
        .value("UINT8", PynetppDType::UINT8)
        .value("UINT16", PynetppDType::UINT16)
        .value("UINT32", PynetppDType::UINT32)
        .value("UINT64", PynetppDType::UINT64)
        .value("FLOAT", PynetppDType::FLOAT)
        .value("DOUBLE", PynetppDType::DOUBLE)
        .export_values();
}