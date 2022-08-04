#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <container.h>

void bind_container(pybind11::module_ &m) {
    pybind11::class_<OpenGymContainer>(
        m,
        "OpenGymContainer"
    );

    pybind11::class_<OpenGymDiscreteContainer, OpenGymContainer>(
        m,
        "OpenGymDiscreteContainer"
    )
        .def(pybind11::init<>())
        .def(pybind11::init<const uint32_t>())
        .def("set_value", &OpenGymDiscreteContainer::set_value)
        .def("get_value", &OpenGymDiscreteContainer::get_value);

    // pybind11::class_<OpenGymBoxContainer<float>, OpenGymContainer>(
    //     m,
    //     "OpenGymBoxContainer",
    //     pybind11::buffer_protocol()
    // )
    //     .def(pybind11::init<>())
    //     .def(pybind11::init<std::vector<uint32_t>>())
    //     .def("add_value", &OpenGymBoxContainer<float>::add_value)
    //     .def("get_value", &OpenGymBoxContainer<float>::get_value)
    //     .def("set_data", &OpenGymBoxContainer<float>::set_data)
    //     .def("get_data", &OpenGymBoxContainer<float>::get_data)
    //     .def("get_shape", &OpenGymBoxContainer<float>::get_shape)
    //     .def_buffer([](OpenGymBoxContainer<float>& c) {
    //         return pybind11::buffer_info(
    //             c.get_data().data(),
    //             sizeof(float),
    //             pybind11::format_descriptor<float>::format(),
    //             1,
    //             {c.get_data().size()},
    //             {sizeof(float)}
    //         );
    //     });

    pybind11::class_<OpenGymBoxContainer<uint64_t>, OpenGymContainer>(
        m,
        "OpenGymBoxContainerUI32",
        pybind11::buffer_protocol()
    )
        .def(pybind11::init<>())
        .def(pybind11::init<std::vector<uint32_t>>())
        // .def("add_value", &OpenGymBoxContainer<uint64_t>::add_value)
        // .def("get_value", &OpenGymBoxContainer<uint64_t>::get_value)
        // .def("set_data", &OpenGymBoxContainer<uint64_t>::set_data)
        // .def("get_data", &OpenGymBoxContainer<uint64_t>::get_data)
        .def("get_shape", &OpenGymBoxContainer<uint64_t>::get_shape)
        // .def("__setitem__", 
        //     [](OpenGymBoxContainer<uint64_t>& c, std::vector<pybind11::ssize_t> i, uint64_t v) {
        //         if (i.size() != c.get_shape().size()) {
        //             throw pybind11::index_error();
        //         }

        //         for (auto idx: i) {
        //             if (idx)
        //         }
        //     }    
        // )
        // .def("from_nparray", []())
        .def_buffer([](OpenGymBoxContainer<uint64_t>& c) {
            std::cout<<c.get_data()<<std::endl;

            return pybind11::buffer_info(
                c.get_data(),
                sizeof(uint64_t),
                pybind11::format_descriptor<uint64_t>::format(),
                c.get_shape().size(),
                c.get_shape(),
                c.get_strides()
            );
        });
        // .def("get_low", &OpenGymBoxSpace::get_low)
        // .def("get_high", &OpenGymBoxSpace::get_high)
        // .def("get_shape", &OpenGymBoxSpace::get_shape);
}