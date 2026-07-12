#pragma once

#include "window/window.hpp"
#include <array>
#include <GLFW/glfw3.h>

enum class MouseButton {
    left,
    middle,
    right,
    COUNT
};

enum class Key {
    Escape,
    W,
    A,
    S,
    D,
    Space,
    Shift,
    COUNT
};

class Input {
public:
    void inputAttachWindow(Window& window);

    void inputUpdate();

    bool inputKeyDown(Key key) const;
    bool inputKeyPressed(Key key) const;
    bool inputKeyReleased(Key key) const;

    bool inputMouseDown(MouseButton mouse_button) const;
    bool inputMousePressed(MouseButton mouse_button) const;
    bool inputMouseReleased(MouseButton mouse_button) const;
    
    float inputMouseDeltaU() const;
    float inputMouseDeltaV() const;

    float inputMouseNormalizedU() const;
    float inputMouseNormalizedV() const;

    void inputSetMouseCaptured(bool captured);
    bool inputMouseCaptured() const;

private:
    GLFWwindow* m_window = nullptr;  // initialize as null pointer

    static constexpr int KEY_COUNT = static_cast<int>(Key::COUNT);
    static constexpr int MOUSE_BUTTON_COUNT = static_cast<int>(MouseButton::COUNT);

    std::array<bool, KEY_COUNT> m_current_keys = {};
    std::array<bool, KEY_COUNT> m_previous_keys = {};

    std::array<bool, MOUSE_BUTTON_COUNT> m_current_mouse_buttons;
    std::array<bool, MOUSE_BUTTON_COUNT> m_previous_mouse_buttons;

    double m_mouse_u = 0.0;
    double m_mouse_v = 0.0;
    double m_previous_mouse_u = 0.0;
    double m_previous_mouse_v = 0.0;

    float m_mouse_delta_u = 0.0f;
    float m_mouse_delta_v = 0.0f;

    bool m_has_previous_mouse_position = false;
    bool m_mouse_captured = false;
};
