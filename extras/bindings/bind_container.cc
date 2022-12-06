#include <container.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

template <typename T = float>
void bind_box_container(pybind11::module_& m, const char* class_name) {
    pybind11::class_<PynetppBoxContainer<T>, PynetppContainer>(
        m, class_name, pybind11::buffer_protocol())
        .def("from_nparray",
             [](pybind11::array_t<T>& array) {
                 pybind11::buffer_info info = array.request();

                 std::vector<uint32_t> shape(info.shape.begin(),
                                             info.shape.end());

                 PynetppBoxContainer<T> c(shape);
                 //  c.set_data((T*)info.ptr);

                 std::memcpy(c.get_data(), info.ptr, info.itemsize * info.size);

                 return c;
             })
        .def_buffer([](PynetppBoxContainer<T>& c) {
            return pybind11::buffer_info(
                c.get_data(), sizeof(T),
                pybind11::format_descriptor<T>::format(), c.get_shape().size(),
                c.get_shape(), c.get_strides());
        });
}

void bind_container(pybind11::module_& m) {
    pybind11::class_<PynetppContainer>(m, "PynetppContainer");

    pybind11::class_<PynetppDiscreteContainer, PynetppContainer>(
        m, "PynetppDiscreteContainer")
        .def(pybind11::init<>())
        .def(pybind11::init<const uint32_t>())
        .def("set_value", &PynetppDiscreteContainer::set_value)
        .def("get_value", &PynetppDiscreteContainer::get_value);

    bind_box_container<int8_t>(m, "PynetppBoxContainerI8");
    bind_box_container<int16_t>(m, "PynetppBoxContainerI16");
    bind_box_container<int32_t>(m, "PynetppBoxContainerI32");
    bind_box_container<int64_t>(m, "PynetppBoxContainerI64");
    bind_box_container<uint8_t>(m, "PynetppBoxContainerUI8");
    bind_box_container<uint16_t>(m, "PynetppBoxContainerUI16");
    bind_box_container<uint32_t>(m, "PynetppBoxContainerUI32");
    bind_box_container<uint64_t>(m, "PynetppBoxContainerUI64");
    bind_box_container<float>(m, "PynetppBoxContainerF");
    bind_box_container<double>(m, "PynettpBoxContainerD");
}