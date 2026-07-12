#pragma once

template <typename T> struct Vector4 {
    T x;
    T y;
    T z;
    T w;
};

using Vector4I = Vector4<int>;
using Vector4F = Vector4<float>;
using Vector4D = Vector4<double>;
