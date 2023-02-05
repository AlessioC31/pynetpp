#include <omnetpp.h>
#include <pybind11/pybind11.h>

extern void bind_spaces(pybind11::module_ &m);
extern void bind_dtypes(pybind11::module_ &m);
extern void bind_container(pybind11::module_ &m);
extern void bind_gymenv(pybind11::module_ &m);
extern void bind_interface(pybind11::module_ &m);

PYBIND11_MODULE(pynetpp_bindings, m) {
    m.doc() = "OMNeT++ python bindings";

    bind_spaces(m);
    bind_dtypes(m);
    bind_container(m);
    bind_gymenv(m);
    bind_interface(m);

    pybind11::register_exception<omnetpp::cTerminationException>(
        m, "TimeLimitError");
}