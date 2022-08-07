#include "container.h"
#include "dtypes.h"
#include <vector>

PynetppDiscreteContainer::PynetppDiscreteContainer(): space_n(0) {}
PynetppDiscreteContainer::PynetppDiscreteContainer(uint32_t n): space_n(n) {}

void PynetppDiscreteContainer::set_value(uint32_t value) {
    if (value >= space_n) {
        throw std::out_of_range("Value is out of range for this container.");
    }

    inner_value = value;
}

uint32_t PynetppDiscreteContainer::get_value() const {
    return inner_value;
}