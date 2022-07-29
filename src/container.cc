#include "container.h"
#include "dtypes.h"
#include <vector>

OpenGymDiscreteContainer::OpenGymDiscreteContainer(): space_n(0) {}
OpenGymDiscreteContainer::OpenGymDiscreteContainer(uint32_t n): space_n(n) {}

void OpenGymDiscreteContainer::set_value(uint32_t value) {
    inner_value = value;
}

uint32_t OpenGymDiscreteContainer::get_value() {
    return inner_value;
}