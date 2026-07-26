#include "textbox.hpp"

namespace {

}

void TextBox::bindTextToBox() {
    m_textbox_text.m_position = {
        m_position.u - 0.95f * m_bounds.width,
        m_position.v - m_bounds.height * 0.5f
    };
    m_textbox_text.m_style = {
        .color = {1.0f, 1.0f, 1.0f},
        .has_background = false,
        .opacity = 1.0f,
        .size = m_bounds.height
    };

    m_textbox_empty_text.m_position = {
        m_position.u - 0.95f * m_bounds.width,
        m_position.v - m_bounds.height * 0.5f
    };
    m_textbox_empty_text.m_style = {
        .color = {0.5f, 0.5f, 0.5f},
        .has_background = false,
        .opacity = 1.0f,
        .size = m_bounds.height
    };
    m_textbox_empty_text.m_string = "type here ...";
    
}

void TextBox::addChar(char char_to_add) {
    m_textbox_text.m_string.push_back(char_to_add);
}

void TextBox::subtractChar() {
    if (m_textbox_text.m_string.empty()) return;
    m_textbox_text.m_string.pop_back();
}

bool TextBox::isHover(const Input& input, float aspect) {
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

void TextBox::processInput(const Input& input, float aspect) {
    m_text_changed = false;
    if (m_is_active) {

        // Subtract Character
        if (input.inputKeyPressed(Key::Delete)) {
            subtractChar();
            m_text_changed = true;
        }

        for (int i = 0; i < static_cast<int>(Key::COUNT); i++) {
            Key key = static_cast<Key>(i);

            // check which/if key pressed
            if (input.inputKeyPressed(static_cast<Key>(key))) {

                // Early Exit Unknown Key
                if (KeyToCharMap.find(key) == KeyToCharMap.end()) return;
                
                // Shifted Keys
                if (input.inputKeyDown(Key::RShift) || input.inputKeyDown(Key::LShift)) {
                    char char_to_add = ShiftedKeyToCharMap.at(key);
                    addChar(char_to_add);
                    m_text_changed = true;
                
                // Regular Keys
                } else {
                    char char_to_add = KeyToCharMap.at(key);
                    addChar(char_to_add);
                    m_text_changed = true;
                }
            }
        }
    }
    if (input.inputMousePressed(MouseButton::left)) {
        if (isHover(input, aspect)) m_is_active = true;
        else m_is_active = false;
    }

}

Primitive TextBox::buildBoxPrimitives() {
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

Primitive TextBox::buildTextPrimitives() {

    // decide which text (empty or not-empty) to use
    if (m_textbox_text.m_string.empty()) m_combined_current_text = m_textbox_empty_text;
    else m_combined_current_text = m_textbox_text;

    return m_combined_current_text.buildPrimitives();
}