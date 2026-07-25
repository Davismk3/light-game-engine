#include "input.hpp"

namespace {
    int toGlfwKey(Key key) {
        switch (key) {
            
            // Letters
            case Key::A: return GLFW_KEY_A;
            case Key::B: return GLFW_KEY_B;
            case Key::C: return GLFW_KEY_C;
            case Key::D: return GLFW_KEY_D;
            case Key::E: return GLFW_KEY_E;
            case Key::F: return GLFW_KEY_F;
            case Key::G: return GLFW_KEY_G;
            case Key::H: return GLFW_KEY_H;
            case Key::I: return GLFW_KEY_I;
            case Key::J: return GLFW_KEY_J;
            case Key::K: return GLFW_KEY_K;
            case Key::L: return GLFW_KEY_L;
            case Key::M: return GLFW_KEY_M;
            case Key::N: return GLFW_KEY_N;
            case Key::O: return GLFW_KEY_O;
            case Key::P: return GLFW_KEY_P;
            case Key::Q: return GLFW_KEY_Q;
            case Key::R: return GLFW_KEY_R;
            case Key::S: return GLFW_KEY_S;
            case Key::T: return GLFW_KEY_T;
            case Key::U: return GLFW_KEY_U;
            case Key::V: return GLFW_KEY_V;
            case Key::W: return GLFW_KEY_W;
            case Key::X: return GLFW_KEY_X;
            case Key::Y: return GLFW_KEY_Y;
            case Key::Z: return GLFW_KEY_Z;

            // Special Keys
            case Key::Escape: return GLFW_KEY_ESCAPE;
            case Key::Space: return GLFW_KEY_SPACE;
            case Key::Shift: return GLFW_KEY_LEFT_SHIFT;

            // Numbers
            case Key::One: return GLFW_KEY_1;
            case Key::Two: return GLFW_KEY_2;
            case Key::Three: return GLFW_KEY_3;
            case Key::Four: return GLFW_KEY_4;
            case Key::Five: return GLFW_KEY_5;
            case Key::Six: return GLFW_KEY_6;
            case Key::Seven: return GLFW_KEY_7;
            case Key::Eight: return GLFW_KEY_8;
            case Key::Nine: return GLFW_KEY_9;
            case Key::Zero: return GLFW_KEY_0;

            // Punctuation Keys
            case Key::Period: return GLFW_KEY_PERIOD;
            case Key::SemiColon: return GLFW_KEY_SEMICOLON;
            case Key::Comma: return GLFW_KEY_COMMA;
            case Key::RSlash: return GLFW_KEY_SLASH;
            case Key::LSlash: return GLFW_KEY_BACKSLASH;
            case Key::QuotationMarkSingle: return GLFW_KEY_APOSTROPHE;
            case Key::Minus: return GLFW_KEY_MINUS;
            case Key::Equal: return GLFW_KEY_EQUAL;
            case Key::LSquareBracket: return GLFW_KEY_LEFT_BRACKET;
            case Key::RSquareBracket: return GLFW_KEY_RIGHT_BRACKET;
            case Key::BackTick: return GLFW_KEY_GRAVE_ACCENT;

            // Shifted characters do not have distinct GLFW key codes.
            case Key::ExclaimationMark:
            case Key::QuestionMark:
            case Key::Colon:
            case Key::UnderScore:
            case Key::QuotationMarkDouble:
            case Key::VerticalLine:
            case Key::At:
            case Key::Hash:
            case Key::Dollar:
            case Key::Percentage:
            case Key::UpCarrot:
            case Key::Amperesand:
            case Key::Cross:
            case Key::LParenthaces:
            case Key::RParenthaces:
            case Key::Plus:
            case Key::LCurvyBracket:
            case Key::RCurvyBracket:
            case Key::LCarrot:
            case Key::RCarrot:
            case Key::Approximation:
                return GLFW_KEY_UNKNOWN;

            case Key::COUNT: break;
        }
        return GLFW_KEY_UNKNOWN;
    }

    int toGlfwMouseButton(MouseButton button) {
        switch (button) {
            case MouseButton::left: return GLFW_MOUSE_BUTTON_LEFT;
            case MouseButton::middle: return GLFW_MOUSE_BUTTON_MIDDLE;
            case MouseButton::right: return GLFW_MOUSE_BUTTON_RIGHT;
            case MouseButton::COUNT: break;
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

        int glfw_key = toGlfwKey(static_cast<Key>(i));
        m_current_keys[i] =
            glfw_key != GLFW_KEY_UNKNOWN &&
            glfwGetKey(m_window, glfw_key) == GLFW_PRESS;
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

float Input::inputMouseWindowU() const {
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

float Input::inputMouseWindowV() const {
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
