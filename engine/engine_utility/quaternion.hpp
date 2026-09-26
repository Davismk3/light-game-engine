#pragma once

#include "vector.hpp"

#include <cmath>

template<typename T> struct Quaternion {
    T w;
    T i;
    T j;
    T k;

    static Quaternion<T> axisAngleQuaternion(Vector3<T> axis, T angle);

    Quaternion<T> quaternionNormalized() const;
    Quaternion<T> quaternionInverse() const;

    Quaternion<T> operator*(const Quaternion& other) const;
    Vector3<T> quaternionRotateVector(Vector3<T> vector) const;
};

using QuaternionF = Quaternion<float>;
using QuaternionD = Quaternion<double>;
