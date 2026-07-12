#pragma once

#include "engine/math/linear_algebra/vec3.hpp"
#include "engine/input/input.hpp"
#include "engine/graphics/mesh/mesh.hpp"
#include "engine/graphics/shader/shader.hpp"
#include "engine/graphics/draw/draw.hpp"

enum class ButtonState {
    Idle,
    Hover,
    Clicked
};

class Button {
public:
    ~Button() = default;

    void initialize(
        float position_u, 
        float position_v, 
        float size,
        Vector3F idle_color,
        Vector3F hover_color,
        Vector3F active_color,
        float opacity
    );

    void processInput(const Input& input);

    bool isHover(const Input& input);
    bool isClicked(const Input& input);

    void drawButton();

private:
    ButtonState m_button_state = ButtonState::Idle;

    Mesh m_button_mesh;
    Shader m_button_shader;
    
    float m_upper_left_corner_u;
    float m_upper_left_corner_v;

    float m_lower_right_corner_u;
    float m_lower_right_corner_v;

    Vector3F m_idle_color;
    Vector3F m_hover_color;
    Vector3F m_active_color;
    float m_opacity;
};
