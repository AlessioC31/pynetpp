#include <cstdint>
#include <vector>
#include <cstring>
#include <numeric>
#include <initializer_list>
#include <stdexcept>
#include <iostream>
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
        OpenGymBoxContainer(const OpenGymBoxContainer& that);
        OpenGymBoxContainer(OpenGymBoxContainer&& that) noexcept;
        ~OpenGymBoxContainer() { delete[] inner_data; }

        // void add_value(T value);
        // T get_value(uint32_t idx);

        // void set_data(std::vector<T> data);
        // std::vector<T> get_data();
        // inline void set_data(T* data) { inner_data = data; }
        inline T* get_data() { return inner_data; }
        inline uint32_t get_size() { return size; }
        inline std::vector<uint32_t> get_strides() { return strides; }
        inline std::vector<uint32_t> get_shape() { return space_shape; }
        inline OpenGymDType get_space_dtype() { return space_dtype; }

        friend void swap(OpenGymBoxContainer& first, OpenGymBoxContainer& second) noexcept {
            using std::swap;

            swap(first.space_shape, second.space_shape);
            swap(first.inner_data, second.inner_data);
            swap(first.strides, second.strides);
            swap(first.size, second.size);
            swap(first.space_dtype, second.space_dtype);
        }

        OpenGymBoxContainer& operator=(OpenGymBoxContainer other);
        T& operator()(std::vector<uint32_t> idxs);
        T operator()(std::vector<uint32_t> idxs) const;

    private:
        std::vector<uint32_t> space_shape;
        T* inner_data;
        std::vector<uint32_t> strides;
        uint32_t size;
        OpenGymDType space_dtype;
};

template<typename T>
OpenGymBoxContainer<T>::OpenGymBoxContainer() {
    space_dtype = get_dtype<T> ();
    inner_data = nullptr;
}

template<typename T>
OpenGymBoxContainer<T>::OpenGymBoxContainer(const OpenGymBoxContainer& that) {
    //TODO: what if that is an empy container (shape.size() == 0)
    space_shape = that.space_shape;
    strides = that.strides;
    size = that.size;
    space_dtype = that.space_dtype;
    inner_data = new T[size] ();

    std::memcpy(inner_data, that.inner_data, sizeof(T) * size);
}

template<typename T>
OpenGymBoxContainer<T>::OpenGymBoxContainer(OpenGymBoxContainer&& that) noexcept : OpenGymBoxContainer() {
    swap(*this, that);
}

template<typename T>
OpenGymBoxContainer<T>& OpenGymBoxContainer<T>::operator=(OpenGymBoxContainer other) {
    swap(*this, other);

    return *this;
}

//TODO: fix throw message with formatting
//TODO: maybe change vector to something else
template<typename T>
T& OpenGymBoxContainer<T>::operator()(std::vector<uint32_t> idxs) {

    if (idxs.size() != space_shape.size()) {
        throw std::invalid_argument("Invalid dimensions numbers.");
        //  throw std::invalid_argument("Expected " + space_shape.size() + " dimensions, got " + idxs.size() + ".", space_shape.size(), idxs.size());
    }

    uint32_t n = space_shape.size();
    uint32_t idx = 0;
    
    for (uint32_t i = 0; i < n; i ++) {
        if (idxs[i] >= space_shape[i]) {
            throw std::invalid_argument("Invalid index.");
            // throw std::out_of_range(std::format("Dimension {} has a size of {} but got index {}.", i, space_shape[i], idxs[i]));
        }

        // strides are in number of bytes so we need to devide by
        // the size of the scalar before using the index to access data
        idx += idxs[i] * strides[i] / sizeof(T);
    }

    return inner_data[idx];
}
        
        
template<typename T>
T OpenGymBoxContainer<T>::operator()(std::vector<uint32_t> idxs) const {
    if (idxs.size() != space_shape.size()) {
        throw std::invalid_argument("Invalid dimensions numbers.");
        //  throw std::invalid_argument("Expected " + space_shape.size() + " dimensions, got " + idxs.size() + ".", space_shape.size(), idxs.size());
    }

    auto n = space_shape.size();
    uint32_t idx = 0;

    for (auto i = 0; i < n; i ++) {
        if (idxs[i] >= space_shape[i]) {
            throw std::invalid_argument("Invalid index.");
            // throw std::out_of_range(std::format("Dimension {} has a size of {} but got index {}.", i, space_shape[i], idxs[i]));
        }

        idx += idxs[i] * strides[i] / sizeof(T);
    }

    return inner_data[idx];
}

template<typename T>
OpenGymBoxContainer<T>::OpenGymBoxContainer(std::vector<uint32_t> shape) {
    space_dtype = get_dtype<T> ();
    space_shape = shape;
    size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<T>());

    uint32_t temp_size = size;

    for (uint32_t dim : space_shape) {
        temp_size /= dim;
        strides.push_back(temp_size * sizeof(T));
    }

    inner_data = new T[size] ();
}

#endif