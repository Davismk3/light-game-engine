#pragma once

#include "engine/math/linear_algebra/mat4.hpp"
#include "engine/math/linear_algebra/vec3.hpp"
#include "engine/math/quaternions/quaternion.hpp"

class Camera {
public:
    Camera();

    void position(const Vector3F& position);
    void rotation(const QuaternionF& rotation);
    
    void perspective(float field_of_view, float aspect_ratio, float near_plane, float far_plane);
    void orthographic(float left, float right, float bottom, float top, float near_plane, float far_plane);

    Matrix4F viewMatrix() const;
    Matrix4F projectionMatrix() const;

    Vector3F m_position;
    QuaternionF m_rotation;
    Matrix4F m_projection;

private:

};