#include "input.hpp"
#include <GLFW/glfw3.h>

namespace {
    int toGlfwKey(Key key) {
        switch (key) {
            case Key::Escape: return GLFW_KEY_ESCAPE;
            case Key::W: return GLFW_KEY_W;
            case Key::A: return GLFW_KEY_A;
            case Key::S: return GLFW_KEY_S;
            case Key::D: return GLFW_KEY_D;
            case Key::Space: return GLFW_KEY_SPACE;
            case Key::Shift: return GLFW_KEY_LEFT_SHIFT;
            case Key::COUNT: break;
        }
        return GLFW_KEY_UNKNOWN;
    }

    int toGlfwMouseButton(MouseButton button) {
        switch (button) {
            case MouseButton::left: return GLFW_MOUSE_BUTTON_LEFT;
            case MouseButton::middle: return GLFW_MOUSE_BUTTON_MIDDLE;
            case MouseButton::right: return GLFW_MOUSE_BUTTON_RIGHT;
        }
        return -1;
    }
}

void Input::inputAttachWindow(Window& window) {
    m_window = window.windowNativeHandle();
}

void Input::inputUpdate() {
    if (!m_window) return;

    for (int i = 0; i < KEY_COUNT; ++i) {        
        m_previous_keys[i] = m_current_keys[i];
        m_current_keys[i] = glfwGetKey(m_window, toGlfwKey(static_cast<Key>(i))) == GLFW_PRESS;
    }

    for (int i = 0; i < MOUSE_BUTTON_COUNT; ++i) {
        m_previous_mouse_buttons[i] = m_current_mouse_buttons[i];
        m_current_mouse_buttons[i] = glfwGetMouseButton(m_window, toGlfwMouseButton(static_cast<MouseButton>(i))) == GLFW_PRESS;
    }

    double mouse_u = 0.0;
    double mouse_v = 0.0;

    glfwGetCursorPos(m_window, &mouse_u, &mouse_v);

    if (!m_has_previous_mouse_position) {
        m_previous_mouse_u = mouse_u;
        m_previous_mouse_v = mouse_v;
        m_has_previous_mouse_position = true;
    }

    m_mouse_u = mouse_u;
    m_mouse_v = mouse_v;

    m_mouse_delta_u = static_cast<float>(m_mouse_u - m_previous_mouse_u);
    m_mouse_delta_v = static_cast<float>(m_mouse_v - m_previous_mouse_v);

    m_previous_mouse_u = m_mouse_u;
    m_previous_mouse_v = m_mouse_v;
}

void Input::inputSetMouseCaptured(bool captured) {
    if (!m_window) return;

    m_mouse_captured = captured;
    m_has_previous_mouse_position = false;

    glfwSetInputMode(m_window, GLFW_CURSOR, captured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool Input::inputMouseCaptured() const {
    return m_mouse_captured;
}

bool Input::inputKeyDown(Key key) const {
    int index = static_cast<int>(key);
    return m_current_keys[index];
}

bool Input::inputKeyPressed(Key key) const {
    int index = static_cast<int>(key);
    return m_current_keys[index] && !m_previous_keys[index];
}

bool Input::inputKeyReleased(Key key) const {
    int index = static_cast<int>(key);
    return !m_current_keys[index] && m_previous_keys[index];
}

bool Input::inputMouseDown(MouseButton mouse_button) const {
    if (!m_window) return false;
    return glfwGetMouseButton(m_window, toGlfwMouseButton(mouse_button)) == GLFW_PRESS;
}

bool Input::inputMousePressed(MouseButton mouse_button) const {
    int index = static_cast<int>(mouse_button);
    return m_current_mouse_buttons[index] && !m_previous_mouse_buttons[index];
}

bool Input::inputMouseReleased(MouseButton mouse_button) const {
    int index = static_cast<int>(mouse_button);
    return !m_current_mouse_buttons[index] && m_previous_mouse_buttons[index];
}

float Input::inputMouseDeltaU() const {
    return m_mouse_delta_u;
}

float Input::inputMouseDeltaV() const {
    return m_mouse_delta_v;
}

float Input::inputMouseNormalizedU() const {
    if (!m_window) return 0.0f;

    int width = 0;
    int height = 0;
    glfwGetWindowSize(m_window, &width, &height);

    if (width == 0) return 0.0f;

    return 2.0f *
           static_cast<float>(m_mouse_u) /
           static_cast<float>(width)
           - 1.0f;
}

float Input::inputMouseNormalizedV() const {
    if (!m_window) return 0.0f;

    int width = 0;
    int height = 0;
    glfwGetWindowSize(m_window, &width, &height);

    if (height == 0) return 0.0f;

    return 1.0f -
           2.0f *
           static_cast<float>(m_mouse_v) /
           static_cast<float>(height);
}
