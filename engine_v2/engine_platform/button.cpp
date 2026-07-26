#include "button.hpp"

Button::Button(Vector2F position, ButtonBounds bounds, ButtonStyle style) {
    m_position = position;
    m_bounds = bounds;
    m_style = style;
}

bool Button::isHover(const Input& input, float aspect) {
    float mouse_u = input.inputMouseWindowU() * aspect;
    float mouse_v = input.inputMouseWindowV();

    const float u_min = m_position.u - m_bounds.width;
    const float u_max = m_position.u + m_bounds.width;
    const float v_min = m_position.v - m_bounds.height;
    const float v_max = m_position.v + m_bounds.height;

    return mouse_u >= u_min &&
           mouse_u <= u_max &&
           mouse_v >= v_min &&
           mouse_v <= v_max;
}

bool Button::isHeld(const Input& input, float aspect) {
    if (isHover(input, aspect) && input.inputMousePressed(MouseButton::left)) return true;
    return false;
}

void Button::processInput(const Input& input, float aspect) {
    if (isHeld(input, aspect)) m_state = ButtonState::Held;
    else if (isHover(input, aspect)) m_state = ButtonState::Hover;
    else m_state = ButtonState::Idle;
}

Primitive Button::buildPrimitives() {
    const float left = m_position.u - m_bounds.width;
    const float right = m_position.u + m_bounds.width;
    const float bottom = m_position.v - m_bounds.height;
    const float top = m_position.v + m_bounds.height;

    return quad(
        {right, top, 0.0f, 1.0f, 1.0f},
        {right, bottom, 0.0f, 1.0f, 0.0f},
        {left, bottom, 0.0f, 0.0f, 0.0f},
        {left, top, 0.0f, 0.0f, 1.0f}
    );
}
