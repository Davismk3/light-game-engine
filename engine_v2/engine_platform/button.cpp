#include "button.hpp"

Button::Button(ButtonBounds bounds, ButtonStyle style) {
    m_bounds = bounds;
    m_style = style;
}

bool Button::isHover(const Input& input) {
    float mouse_u = input.inputMouseWindowU();
    float mouse_v = input.inputMouseWindowV();

    const float u_min = m_bounds.u - m_bounds.width;
    const float u_max = m_bounds.u + m_bounds.width;
    const float v_min = m_bounds.v - m_bounds.height;
    const float v_max = m_bounds.v + m_bounds.height;

    return mouse_u >= u_min &&
           mouse_u <= u_max &&
           mouse_v >= v_min &&
           mouse_v <= v_max;
}

bool Button::isHeld(const Input& input) {
    if (isHover(input) && input.inputMouseDown(MouseButton::left)) return true;
    return false;
}

void Button::update(const Input& input) {
    if (isHeld(input)) m_state = ButtonState::Held;
    else if (isHover(input)) m_state = ButtonState::Hover;
    else m_state = ButtonState::Idle;
}
