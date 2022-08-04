#include <container.h>
#include <dtypes.h>
#include <iostream>
#include <cassert>

void test_container_default_ctor() {
    OpenGymBoxContainer<float> c;

    assert(c.get_data() == nullptr);
    assert(c.get_space_dtype() == OpenGymDType::FLOAT);

    assert(c.get_shape().size() == 0);
    assert(c.get_strides().size() == 0);
    assert(c.get_size() == 0);
}

void test_container_shape_ctor() {
    OpenGymBoxContainer<float> c({3, 4, 5});

    assert(c.get_data() != nullptr);
    assert(c.get_space_dtype() == OpenGymDType::FLOAT);
    
    assert(c.get_shape().size() == 3);
    assert(c.get_shape()[0] == 3);
    assert(c.get_shape()[1] == 4);
    assert(c.get_shape()[2] == 5);

    assert(c.get_strides().size() == 3);

    assert(c.get_strides()[0] == sizeof(float) * 20);
    assert(c.get_strides()[1] == sizeof(float) * 5);
    assert(c.get_strides()[2] == sizeof(float) * 1);

    assert(c.get_size() == 60);
}

void test_container_operator() {
    OpenGymBoxContainer<float> c({3, 4, 5});

    c({0, 0, 0}) = 5;

    assert(c({0, 0, 0}) == 5);
}

void test_container_copy() {
    OpenGymBoxContainer<float> c({3, 4, 5});

    assert(c({0, 0, 0}) == 0.0f);

    OpenGymBoxContainer<float> d = c;

    assert(d({0, 0, 0}) == 0.0f);

    d({0, 0, 0}) = 5;

    assert(d({0, 0, 0}) == 5);

    std::cout<<c({0, 0, 0})<<std::endl;
    assert(c({0, 0, 0}) == 0.0f);
    
}

int main() {
    test_container_default_ctor();
    test_container_shape_ctor();
    test_container_operator();
    test_container_copy();
    return 0;
}