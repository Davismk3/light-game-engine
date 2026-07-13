#pragma once

#include "../engine_core/quaternion.hpp"
#include "../engine_core/vector.hpp"
#include "../engine_core/matrix.hpp"

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
