#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <container.h>

void bind_container(pybind11::module_ &m) {
    pybind11::class_<PynetppContainer>(
        m,
        "PynetppContainer"
    );

    pybind11::class_<PynetppDiscreteContainer, PynetppContainer>(
        m,
        "PynetppDiscreteContainer"
    )
        .def(pybind11::init<>())
        .def(pybind11::init<const uint32_t>())
        .def("set_value", &PynetppDiscreteContainer::set_value)
        .def("get_value", &PynetppDiscreteContainer::get_value);

    pybind11::class_<PynetppBoxContainer<float>, PynetppContainer>(
        m,
        "PynetppBoxContainerF",
        pybind11::buffer_protocol()
    )
        .def("from_nparray", [](pybind11::array_t<float>& array) {
            pybind11::buffer_info info = array.request();

            std::vector<uint32_t> shape(info.shape.begin(), info.shape.end());

            PynetppBoxContainer<float> c(shape);     

            std::memcpy(c.get_data(), info.ptr, info.itemsize * info.size);

            return c;
        })
        .def_buffer([](PynetppBoxContainer<float>& c) {
            return pybind11::buffer_info(
                c.get_data(),
                sizeof(float),
                pybind11::format_descriptor<float>::format(),
                c.get_shape().size(),
                c.get_shape(),
                c.get_strides()
            );
        });

    pybind11::class_<PynetppBoxContainer<uint32_t>, PynetppContainer>(
        m,
        "PynetppBoxContainerUI32",
        pybind11::buffer_protocol()
    )
        .def("from_nparray", [](pybind11::array_t<uint32_t>& array) {
            pybind11::buffer_info info = array.request();

            std::vector<uint32_t> shape(info.shape.begin(), info.shape.end());

            PynetppBoxContainer<uint32_t> c(shape);     

            std::memcpy(c.get_data(), info.ptr, info.itemsize * info.size);

            return c;
        })
        .def_buffer([](PynetppBoxContainer<uint32_t>& c) {
            return pybind11::buffer_info(
                c.get_data(),
                sizeof(uint32_t),
                pybind11::format_descriptor<uint32_t>::format(),
                c.get_shape().size(),
                c.get_shape(),
                c.get_strides()
            );
        });
}