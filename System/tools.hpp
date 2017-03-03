#pragma once
#include <type_traits>
#include <iostream>
#include <GL/glew.h>
#include "System/glm.hpp"

unsigned nextPowerOfTwo(unsigned number);

struct DrawElements {
    GLuint count = 0;
    GLuint primCount = 0;
    GLuint firstIndex = 0;
    GLint  baseVertex = 0;
    GLuint baseInstance = 0;
};

struct DrawArrays {
    GLuint count = 0;
    GLuint primCount = 0;
    GLuint first = 0;
    GLuint baseInstance = 0;
};

inline std::ostream &operator<<(std::ostream &stream, glm::vec2 v) {
    stream << v.x << " " << v.y;
    return stream;
}

inline std::ostream &operator<<(std::ostream &stream, glm::vec3 v) {
    stream << v.x << " " << v.y << " " << v.z;
    return stream;
}

inline std::ostream &operator<<(std::ostream &stream, glm::vec4 v) {
    stream << v.x << " " << v.y << " " << v.z << " " << v.w;
    return stream;
}

// writing
template<template<typename, typename...> class Container, typename T, typename ...A>
std::ostream &operator<<(std::ostream &stream, Container<T, A...> const &c) {
    for(auto const &e : c)
        stream << e << " ";
    stream << std::endl;
    return stream;
}

// Appending
template<template<typename, typename...> class Container, typename T, typename V, typename ...A>
Container<T, A...> &operator<<(Container<T, A...> &c, V const &v) {
    c.emplace_back(v);
    return c;
}

// Output must not be an ostream
template<template<typename, typename> class Output, template<typename, typename> class Input,
         typename T1, typename A1, typename T2, typename A2>
std::enable_if_t<!std::is_base_of<std::ostream, Output<T1, A1>>::value, Output<T1, A1>&>
operator<<(Output<T1, A1> &o, Input<T2, A2> const &i) {
    std::copy(i.begin(), i.end(), std::back_inserter(o));
    return o;
}

template<typename T>
T min(T a, T b) {
    return std::min(a, b);
}

template<typename T, typename ...Args>
T min(T a, T b, Args ...args) {
    return min(a, min(b, args...));
}

template<typename T>
T max(T a, T b) {
    return std::max(a, b);
}

template<typename T, typename ...Args>
T max(T a, T b, Args ...args) {
    return max(a, max(b, args...));
}
