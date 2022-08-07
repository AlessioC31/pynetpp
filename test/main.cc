#include <container.h>
#include <dtypes.h>

#include <cassert>
#include <iostream>

void test_container_default_ctor() {
    PynetppBoxContainer<float> c;

    assert(c.get_data() == nullptr);
    assert(c.get_space_dtype() == PynetppDType::FLOAT);

    assert(c.get_shape().size() == 0);
    assert(c.get_strides().size() == 0);
    assert(c.get_size() == 0);
}

void test_container_shape_ctor() {
    PynetppBoxContainer<float> c({3, 4, 5});

    assert(c.get_data() != nullptr);
    assert(c.get_space_dtype() == PynetppDType::FLOAT);

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
    PynetppBoxContainer<float> c({3, 4, 5});

    c({0, 0, 0}) = 5;

    assert(c({0, 0, 0}) == 5);
}

void test_container_copy() {
    PynetppBoxContainer<float> c({3, 4, 5});

    assert(c({1, 1, 1}) == 0.0f);

    PynetppBoxContainer<float> d = c;

    assert(d({1, 1, 1}) == 0.0f);

    d({1, 1, 1}) = 5;

    assert(d({1, 1, 1}) == 5);
    assert(c({1, 1, 1}) == 0.0f);
}

void test_container_type() {
    PynetppBoxContainer<float> c;

    assert(c.get_type() == "box_float");

    PynetppBoxContainer<uint32_t> d;
    assert(d.get_type() == "box_uint32_t");
}

int main() {
    test_container_default_ctor();
    test_container_shape_ctor();
    test_container_operator();
    test_container_copy();
    test_container_type();

    return 0;
}