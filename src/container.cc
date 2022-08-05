#include "container.h"
#include "dtypes.h"
#include <vector>

PynetppDiscreteContainer::PynetppDiscreteContainer(): space_n(0) {}
PynetppDiscreteContainer::PynetppDiscreteContainer(uint32_t n): space_n(n) {}

void PynetppDiscreteContainer::set_value(uint32_t value) {
    inner_value = value;
}

uint32_t PynetppDiscreteContainer::get_value() {
    return inner_value;
}