#include "button.hpp"
#include <iostream>

void Button::initialize(
    float position_u, 
    float position_v, 
    float size,
    Vector3F idle_color,
    Vector3F hover_color,
    Vector3F active_color,
    float opacity
) {
    m_upper_left_corner_u = position_u - size;
    m_upper_left_corner_v = position_v + size;

    m_lower_right_corner_u = position_u + size;
    m_lower_right_corner_v = position_v - size;

    m_idle_color = idle_color;
    m_hover_color = hover_color;
    m_active_color = active_color;

    m_opacity = opacity;

    m_button_mesh.meshAppend(quad(
        {m_lower_right_corner_u, m_upper_left_corner_v, 0.0f, 1.0f, 1.0f},
        {m_lower_right_corner_u, m_lower_right_corner_v, 0.0f, 1.0f, 0.0f},
        {m_upper_left_corner_u, m_lower_right_corner_v, 0.0f, 0.0f, 0.0f},
        {m_upper_left_corner_u, m_upper_left_corner_v, 0.0f, 0.0f, 1.0f}
    ));
    m_button_mesh.meshUpload();

    m_button_shader.shaderInitialize("assets/shaders/basic.vert", "assets/shaders/solid.frag");
    m_button_shader.shaderUse();
    m_button_shader.shaderSetFloat("u_opacity", m_opacity);
    m_button_shader.shaderSetVec3("u_tint", m_idle_color.x, m_idle_color.y, m_idle_color.z);
}

void Button::processInput(const Input& input) {
    if (isClicked(input)) m_button_state = ButtonState::Clicked;
    else if (isHover(input)) m_button_state = ButtonState::Hover; 
    else m_button_state = ButtonState::Idle;
}

bool Button::isHover(const Input& input) {   
    float mouse_u = input.inputMouseNormalizedU();
    float mouse_v = input.inputMouseNormalizedV();

    if (
        mouse_u <= m_lower_right_corner_u && 
        mouse_u >= m_upper_left_corner_u &&
        mouse_v <= m_upper_left_corner_v &&
        mouse_v >= m_lower_right_corner_v
    ) {
        return true;
    }
    return false;
}

bool Button::isClicked(const Input& input) {
    if (isHover(input) && input.inputMousePressed(MouseButton::left)) return true;
    return false;
}

void Button::drawButton() {
    m_button_shader.shaderUse();

    if (m_button_state == ButtonState::Hover) m_button_shader.shaderSetVec3("u_tint", m_hover_color.x, m_hover_color.y, m_hover_color.z);
    else if (m_button_state == ButtonState::Clicked) m_button_shader.shaderSetVec3("u_tint", m_active_color.x, m_active_color.y, m_active_color.z);
    else m_button_shader.shaderSetVec3("u_tint", m_idle_color.x, m_idle_color.y, m_idle_color.z);
    
    drawMesh(m_button_mesh, m_button_shader);
}
