#include <cstdint>
#include <vector>
#include "dtypes.h"

#ifndef gym_env_container
#define gym_env_container

class OpenGymContainer {
    public:
        OpenGymContainer() {};
        // virtual ~OpenGymContainer();
};

class OpenGymDiscreteContainer : public OpenGymContainer{
    public:
        OpenGymDiscreteContainer();
        OpenGymDiscreteContainer(uint32_t n);
        // virtual ~OpenGymDiscreteContainer();

        void set_value(uint32_t value);
        uint32_t get_value();

    private:
        uint32_t space_n;
        uint32_t inner_value;
};

template<typename T = float>
class OpenGymBoxContainer : public OpenGymContainer{
    public:
        OpenGymBoxContainer();
        OpenGymBoxContainer(std::vector<uint32_t> shape);
        // virtual ~OpenGymBoxContainer();

        void add_value(T value);
        T get_value(uint32_t idx);

        void set_data(std::vector<T> data);
        std::vector<T> get_data();

        std::vector<uint32_t> get_shape();

    private:
        std::vector<uint32_t> space_shape;
        std::vector<T> inner_data;
        OpenGymDType space_dtype;
};

template<typename T>
OpenGymBoxContainer<T>::OpenGymBoxContainer() {
    space_dtype = get_dtype<T> ();
}

template<typename T>
OpenGymBoxContainer<T>::OpenGymBoxContainer(std::vector<uint32_t> shape) {
    space_dtype = get_dtype<T> ();
    space_shape = shape;
}

template<typename T>
void OpenGymBoxContainer<T>::add_value(T value) {
    inner_data.push_back(value);
}

template<typename T>
T OpenGymBoxContainer<T>::get_value(uint32_t idx) {
    if (idx < inner_data.size()) {
        return inner_data[idx];
    } else {
        // TODO: throw?
        return 0;
    }
}

template<typename T>
void OpenGymBoxContainer<T>::set_data(std::vector<T> data) {
    inner_data = data;
}

template<typename T>
std::vector<T> OpenGymBoxContainer<T>::get_data() {
    return inner_data;
}

template<typename T>
std::vector<uint32_t> OpenGymBoxContainer<T>::get_shape() {
    return space_shape;
}

#endif