#pragma once

#include "vector.hpp"
#include "quaternion.hpp"

template <typename T> struct Matrix4 {
    T m[4][4];

    // Construction
    static Matrix4<T> identityMatrix();
    static Matrix4<T> translationMatrix(const Vector3<T>& position);
    static Matrix4<T> scaleMatrix(const Vector3<T>& scale);
    static Matrix4<T> rotationMatrix(const Quaternion<T>& q);

    // Construction Graphics-Specific (USE FLOAT TYPES)
    static Matrix4<T> lookAtMatrix(const Vector3F& eye, const Vector3F& target, const Vector3F& up);
    static Matrix4<T> perspectiveMatrix(float field_of_view, float aspect_ratio, float near_plane, float far_plane);
    static Matrix4<T> orthographicMatrix(float left, float right, float bottom, float top, float near_plane, float far_plane);

    // Operators
    Matrix4<T> operator+(const Matrix4<T>& rhs) const;
    Matrix4<T> operator-(const Matrix4<T>& rhs) const;
    Matrix4<T> operator*(const Matrix4<T>& rhs) const;
    Vector4<T> operator*(const Vector4<T>& rhs) const;
    Matrix4<T> operator*(const T& scalar) const;
    Matrix4<T>& operator*=(const Matrix4<T>& rhs);

    // Utilities
    bool matrixIsIdentity() const;
    const T* matrixData() const;
    Vector4<T> matrixRow(int row) const;
    Vector4<T> matrixColumn(int column) const;
};

using Matrix4F = Matrix4<float>;
using Matrix4D = Matrix4<double>;

template<typename T> Matrix4<T> Matrix4<T>::identityMatrix() {
    Matrix4<T> matrix{};
    matrix.m[0][0] = 1;
    matrix.m[1][1] = 1;
    matrix.m[2][2] = 1;
    matrix.m[3][3] = 1;

    return matrix;
}

template<typename T> Matrix4<T> Matrix4<T>::translationMatrix(const Vector3<T>& position) {
    Matrix4<T> matrix = identityMatrix();
    matrix.m[0][3] = position.x;
    matrix.m[1][3] = position.y;
    matrix.m[2][3] = position.z;

    return matrix;
}

template<typename T> Matrix4<T> Matrix4<T>::scaleMatrix(const Vector3<T>& scale) {
    Matrix4<T> matrix{};
    matrix.m[0][0] = scale.x;
    matrix.m[1][1] = scale.y;
    matrix.m[2][2] = scale.z;
    matrix.m[3][3] = 1;

    return matrix;
}

template<typename T> Matrix4<T> Matrix4<T>::rotationMatrix(const Quaternion<T>& q) {
    Matrix4<T> matrix = identityMatrix();

    T ii = q.i * q.i;
    T jj = q.j * q.j;
    T kk = q.k * q.k;

    T ij = q.i * q.j;
    T ik = q.i * q.k;
    T jk = q.j * q.k;

    T wi = q.w * q.i;
    T wj = q.w * q.j;
    T wk = q.w * q.k;

    matrix.m[0][0] = 1 - 2 * (jj + kk);
    matrix.m[0][1] = 2 * (ij - wk);
    matrix.m[0][2] = 2 * (ik + wj);

    matrix.m[1][0] = 2 * (ij + wk);
    matrix.m[1][1] = 1 - 2 * (ii + kk);
    matrix.m[1][2] = 2 * (jk - wi);

    matrix.m[2][0] = 2 * (ik - wj);
    matrix.m[2][1] = 2 * (jk + wi);
    matrix.m[2][2] = 1 - 2 * (ii + jj);

    return matrix;
}

template<typename T> Matrix4<T> Matrix4<T>::lookAtMatrix(const Vector3F& eye, const Vector3F& target, const Vector3F& up) {
    Matrix4<T> matrix{};

    Vector3F forward = (target - eye).vectorNormalized();
    Vector3F right = crossProduct(forward, up).vectorNormalized();
    Vector3F corrected_up = crossProduct(right, forward);

    matrix.m[0][0] = right.x;
    matrix.m[0][1] = right.y;
    matrix.m[0][2] = right.z;
    matrix.m[0][3] = dotProduct(right * -1.0f, eye);

    matrix.m[1][0] = corrected_up.x;
    matrix.m[1][1] = corrected_up.y;
    matrix.m[1][2] = corrected_up.z;
    matrix.m[1][3] = dotProduct(corrected_up * -1.0f, eye);
    
    matrix.m[2][0] = forward.x * -1.0f;
    matrix.m[2][1] = forward.y * -1.0f;
    matrix.m[2][2] = forward.z * -1.0f;
    matrix.m[2][3] = dotProduct(forward, eye);

    matrix.m[3][3] = 1.0f;

    return matrix;
}

template<typename T> Matrix4<T> Matrix4<T>::perspectiveMatrix(float field_of_view, float aspect_ratio, float near_plane, float far_plane) {
    Matrix4<T> matrix{};
    
    float f = 1.0f / (std::tan(field_of_view / 2.0f));

    matrix.m[0][0] = f / aspect_ratio;
    matrix.m[1][1] = f;
    matrix.m[2][2] = (far_plane + near_plane) / (near_plane - far_plane);
    matrix.m[2][3] = (2 * far_plane * near_plane) / (near_plane - far_plane);
    matrix.m[3][2] = -1.0f;

    return matrix;
}

template<typename T> Matrix4<T> Matrix4<T>::orthographicMatrix(
    float left,
    float right,
    float bottom,
    float top,
    float near_plane,
    float far_plane
) {
    Matrix4<T> matrix{};

    matrix.m[0][0] = 2.0f / (right - left);
    matrix.m[1][1] = 2.0f / (top - bottom);
    matrix.m[2][2] = -2.0f / (far_plane - near_plane);
    matrix.m[3][3] = 1.0f;

    matrix.m[0][3] = -(right + left) / (right - left);
    matrix.m[1][3] = -(top + bottom) / (top - bottom);
    matrix.m[2][3] = -(far_plane + near_plane) / (far_plane - near_plane);

    return matrix;
}

template<typename T> Matrix4<T> Matrix4<T>::operator+(const Matrix4<T>& rhs) const {
    Matrix4<T> result{};
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            result.m[row][column] = m[row][column] + rhs.m[row][column];
        }
    }
    return result;
}

template<typename T> Matrix4<T> Matrix4<T>::operator-(const Matrix4<T>& rhs) const {
    Matrix4<T> result{};
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            result.m[row][column] = m[row][column] - rhs.m[row][column];
        }
    }
    return result;
}

template<typename T> Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& rhs) const {
    Matrix4<T> result{};
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            for (int i = 0; i < 4; ++i) {
                result.m[row][column] += m[row][i] * rhs.m[i][column];
            }
        }
    }
    return result;
}

template<typename T> Vector4<T> Matrix4<T>::operator*(const Vector4<T>& rhs) const {
    return Vector4<T>{
        m[0][0] * rhs.x + m[0][1] * rhs.y + m[0][2] * rhs.z + m[0][3] * rhs.w,
        m[1][0] * rhs.x + m[1][1] * rhs.y + m[1][2] * rhs.z + m[1][3] * rhs.w,
        m[2][0] * rhs.x + m[2][1] * rhs.y + m[2][2] * rhs.z + m[2][3] * rhs.w,
        m[3][0] * rhs.x + m[3][1] * rhs.y + m[3][2] * rhs.z + m[3][3] * rhs.w
    };
}

template<typename T> Matrix4<T> Matrix4<T>::operator*(const T& scalar) const {
    Matrix4<T> result{};
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            result.m[row][column] = m[row][column] * scalar;
        }
    }
    return result;
}

template<typename T> Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& rhs) {
    *this = *this * rhs;
    return *this;
}

template<typename T> bool Matrix4<T>::matrixIsIdentity() const {
    Matrix4<T> identity = identityMatrix();
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            if (m[row][column] != identity.m[row][column]) {
                return false;
            }
        }
    }
    return true;
}

template<typename T> const T* Matrix4<T>::matrixData() const {
    return &m[0][0];
}

template<typename T> Vector4<T> Matrix4<T>::matrixRow(int row) const {
    return Vector4<T>{
        m[row][0],
        m[row][1],
        m[row][2],
        m[row][3]
    };
}

template<typename T> Vector4<T> Matrix4<T>::matrixColumn(int column) const {
    return Vector4<T>{
        m[0][column],
        m[1][column],
        m[2][column],
        m[3][column]
    };
}
