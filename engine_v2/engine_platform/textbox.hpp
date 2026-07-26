#pragma once

#include "input.hpp"
#include "../engine_render/text.hpp"

#include <map>

enum class TextBoxState {
    Idle, 
    Hover,
    Held
};

struct TextBoxBounds {
    float width;
    float height;
};

struct TextBoxStyle {
    Vector3F idle_color;
    Vector3F hover_color;
    Vector3F typing_color;
    float opacity = 1.0f;
    bool centered;  // the start position is now the center of the text display
};

inline std::map<Key, char> KeyToCharMap {
    {Key::A, 'a'},
    {Key::B, 'b'},
    {Key::C, 'c'},
    {Key::D, 'd'},
    {Key::E, 'e'},
    {Key::F, 'f'},
    {Key::G, 'g'},
    {Key::H, 'h'},
    {Key::I, 'i'},
    {Key::J, 'j'},
    {Key::K, 'k'},
    {Key::L, 'l'},
    {Key::M, 'm'},
    {Key::N, 'n'},
    {Key::O, 'o'},
    {Key::P, 'p'},
    {Key::Q, 'q'},
    {Key::R, 'r'},
    {Key::S, 's'},
    {Key::T, 't'},
    {Key::U, 'u'},
    {Key::V, 'v'},
    {Key::W, 'w'},
    {Key::X, 'x'},
    {Key::Y, 'y'},
    {Key::Z, 'z'},
    {Key::Space, ' '},
    {Key::One, '1'},
    {Key::Two, '2'},
    {Key::Three, '3'},
    {Key::Four, '4'},
    {Key::Five, '5'},
    {Key::Six, '6'},
    {Key::Seven, '7'},
    {Key::Eight, '8'},
    {Key::Nine, '9'},
    {Key::Zero, '0'},
    {Key::Period, '.'},
    {Key::SemiColon, ';'},
    {Key::Comma, ','},
    {Key::RSlash, '/'},
    {Key::LSlash, '\\'},
    {Key::QuotationMarkSingle, '\''},
    {Key::Minus, '-'},
    {Key::Equal, '='},
    {Key::LSquareBracket, '['},
    {Key::RSquareBracket, ']'},
    {Key::BackTick, '`'},
};

inline std::map<Key, char> ShiftedKeyToCharMap {
    {Key::A, 'A'},
    {Key::B, 'B'},
    {Key::C, 'C'},
    {Key::D, 'D'},
    {Key::E, 'E'},
    {Key::F, 'F'},
    {Key::G, 'G'},
    {Key::H, 'H'},
    {Key::I, 'I'},
    {Key::J, 'J'},
    {Key::K, 'K'},
    {Key::L, 'L'},
    {Key::M, 'M'},
    {Key::N, 'N'},
    {Key::O, 'O'},
    {Key::P, 'P'},
    {Key::Q, 'Q'},
    {Key::R, 'R'},
    {Key::S, 'S'},
    {Key::T, 'T'},
    {Key::U, 'U'},
    {Key::V, 'V'},
    {Key::W, 'W'},
    {Key::X, 'X'},
    {Key::Y, 'Y'},
    {Key::Z, 'Z'},
    {Key::Space, ' '},
    {Key::One, '!'},
    {Key::Two, '@'},
    {Key::Three, '#'},
    {Key::Four, '$'},
    {Key::Five, '%'},
    {Key::Six, '^'},
    {Key::Seven, '&'},
    {Key::Eight, '*'},
    {Key::Nine, '('},
    {Key::Zero, ')'},
    {Key::Period, '>'},
    {Key::SemiColon, ':'},
    {Key::Comma, '<'},
    {Key::RSlash, '?'},
    {Key::LSlash, '|'},
    {Key::QuotationMarkSingle, '"'},
    {Key::Minus, '_'},
    {Key::Equal, '+'},
    {Key::LSquareBracket, '{'},
    {Key::RSquareBracket, '}'},
    {Key::BackTick, '~'},
};

class TextBox {
    // the 'textbox' is something the user can interact with and change its text with the keyboard
public:
    TextBox() = default;

    void bindTextToBox();
    void processInput(const Input& input, float aspect);
    //void update(float delta_time);
    void addChar(char char_to_add);
    void subtractChar();

    bool isHover(const Input& input, float aspect);

    Primitive buildBoxPrimitives();
    Primitive buildTextPrimitives();

    bool m_is_active = false;
    bool m_text_changed = false;

    Vector2F m_position;
    TextBoxBounds m_bounds;
    TextBoxStyle m_style;

    Text m_textbox_empty_text;
    Text m_textbox_text;
    Text m_textbox_cursor;
    // -
    Text m_combined_current_text;

    TextBoxState m_state = TextBoxState::Idle;
};
