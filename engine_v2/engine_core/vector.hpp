#pragma once

#include <cmath>

template <typename T> struct Vector4 {
    T x;
    T y;
    T z;
    T w;
};

using Vector4I = Vector4<int>;
using Vector4F = Vector4<float>;
using Vector4D = Vector4<double>;

template <typename T> struct Vector3 {
    T x;
    T y;
    T z;

    T vectorMagnitude() const;
    Vector3<T> vectorNormalized() const;

    Vector3<T> operator+(const Vector3<T>& other) const;
    Vector3<T> operator-(const Vector3<T>& other) const;

    Vector3<T> operator+(T scalar) const;
    Vector3<T> operator-(T scalar) const;
    Vector3<T> operator*(T scalar) const;
    Vector3<T> operator/(T scalar) const;

    bool operator==(const Vector3<T>& other) const;
    bool operator<(const Vector3<T>& other) const;
};

using Vector3I = Vector3<int>;
using Vector3F = Vector3<float>;
using Vector3D = Vector3<double>;

template <typename T> T dotProduct(const Vector3<T>& a, const Vector3<T>& b);
template <typename T> Vector3<T> crossProduct(const Vector3<T>& a, const Vector3<T>& b);

template <typename T> T Vector3<T>::vectorMagnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

template <typename T> Vector3<T> Vector3<T>::vectorNormalized() const {
    T mag = vectorMagnitude();
    T eps = static_cast<T>(1e-8);
    if (mag < eps) return {0, 0, 0};
    
    return {x / mag, y / mag, z / mag};
}

template <typename T> Vector3<T> Vector3<T>::operator+(const Vector3<T>& other) const {
    return {x + other.x, y + other.y, z + other.z};
}

template <typename T> Vector3<T> Vector3<T>::operator-(const Vector3<T>& other) const {
    return {x - other.x, y - other.y, z - other.z};
}

template <typename T> Vector3<T> Vector3<T>::operator+(T scalar) const {
    return {x + scalar, y + scalar, z + scalar};
}

template <typename T> Vector3<T> Vector3<T>::operator-(T scalar) const {
    return {x - scalar, y - scalar, z - scalar};
}

template <typename T> Vector3<T> Vector3<T>::operator*(T scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

template <typename T> Vector3<T> Vector3<T>::operator/(T scalar) const {
    T eps = static_cast<T>(1e-8);
    return {x / (scalar + eps), y / (scalar + eps), z / (scalar + eps)};
}

template <typename T> bool Vector3<T>::operator==(const Vector3<T>& other) const {
    return x == other.x && y == other.y && z == other.z;
}

template <typename T> bool Vector3<T>::operator<(const Vector3<T>& other) const {
    if (x != other.x) return x < other.x;
    if (y != other.y) return y < other.y;
    return z < other.z;
}

template <typename T> T dotProduct(const Vector3<T>& a, const Vector3<T>& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T> Vector3<T> crossProduct(const Vector3<T>& a, const Vector3<T>& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
