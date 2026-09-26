#include "camera.hpp"

Camera::Camera() {
    m_position = {0.0f, 0.0f, 0.0f};
    m_rotation = {1.0f, 0.0f, 0.0f, 0.0f};
    m_projection = Matrix4F::identityMatrix();
}

void Camera::position(const Vector3F& position) {
    m_position = position;
}

void Camera::rotation(const QuaternionF& rotation) {
    m_rotation = rotation;
}

void Camera::perspective(float field_of_view, float aspect_ratio, float near_plane, float far_plane) {
    field_of_view *= 3.1415926f / 180.0f;  // degrees to radians
    m_projection = Matrix4F::perspectiveMatrix(field_of_view, aspect_ratio, near_plane, far_plane);
}

void Camera::orthographic(float left, float right, float bottom, float top, float near_plane, float far_plane) {
    m_projection = Matrix4F::orthographicMatrix(left, right, bottom, top, near_plane, far_plane);
}

Matrix4F Camera::viewMatrix() const {
    Vector3F forward = m_rotation.quaternionRotateVector({0.0f, 0.0f, -1.0f});
    Vector3F up = m_rotation.quaternionRotateVector({0.0f, 1.0f, 0.0f});
    Vector3F target = m_position + forward;

    return Matrix4F::lookAtMatrix(m_position, target, up);
}

Matrix4F Camera::projectionMatrix() const {
    return m_projection;
}
