#pragma once

#include "../engine_utility/vector.hpp"
#include "../engine_render/primitive.hpp"
#include "../engine_render/texture.hpp"
#include "../engine_platform/input.hpp"
#include "../engine_config.hpp"

#include <string>
#include <iostream>
#include <map>

/*
This script contains Text and Textbox objects. 
*/

// Whether the text's start position is to the left, right, or center of the string.
enum class TextPositioning {
    LeftToRight,
    RightToLeft,
    Centered,
};

// State of the textbox.
enum class TextBoxState {
    Idle, 
    Hover,
    Active
};

// Glyph UVs for the menu atlas.
struct GlyphAtlasPositionUV {
    int u;
    int v;
};

// Configurations for the text color, size, background, opacity, and positioning.
struct TextConfig {
    float size;
    Vector3F color = {0.0f, 0.0f, 0.0f};
    TextPositioning positioning = TextPositioning::LeftToRight;  // the start position is now the center of the text display
    Vector3F shadow_color = {0.0f, 0.0f, 0.0f};
    bool has_shadow = false;
    bool has_background = false;
    Vector3F background_color = {0.0f, 0.0f, 0.0f};
    float background_opacity = 1.0f;
    float opacity = 1.0f;
};

// Configurations for the textbox colors, height/width, and opacity.
struct TextBoxConfig {
    float height;
    float width;
    Vector3F hover_color;
    Vector3F idle_color;
    Vector3F typing_color;
    float opacity = 1.0f;
};

// Text object.
struct Text {
    Text() = default;
    Text(Vector2F start_position, TextConfig style, std::string string);

    std::string m_string;
    char m_special_init = '\\';
    float m_string_length = 0.0f;

    Vector2F m_start_position;  // normalized to ([-1, 1], [-1, 1]) for screen
    Vector2F m_end_position = m_start_position;  // normalized to ([-1, 1], [-1, 1]) for screen
    TextConfig m_config;

    bool allows_special_characters = false;
    bool follows_cursor = false;

    Primitive buildPrimitives();
};

// Textbox object.
class TextBox {
public:
    TextBox() = default;
    void initializeDefault();
    void processInput(const Input& input, float aspect);
    void addChar(char char_to_add);
    void subtractChar();

    bool isHover(const Input& input, float aspect);

    Primitive buildBoxPrimitives();
    Primitive buildTextPrimitives();
    Primitive buildCursorPrimitives();

    bool m_is_active = false;
    bool m_text_changed = false;
    bool m_state_just_changed = false;

    Vector2F m_position;
    TextBoxConfig m_config;

    Text m_textbox_empty_text;
    Text m_textbox_text;
    Text m_textbox_cursor;
    Text m_combined_current_text;

    TextBoxState m_state = TextBoxState::Idle;

    bool m_string_at_max_length = false;
};

// Map for glyph to glyph ID.
inline std::map<char, int> Glyph_To_GlyphId_Map {
    {'A', 1},
    {'B', 2},
    {'C', 3},
    {'D', 4},
    {'E', 5},
    {'F', 6},
    {'G', 7},
    {'H', 8},
    {'I', 9},
    {'J', 10},
    {'K', 11},
    {'L', 12},
    {'M', 13},
    {'N', 14},
    {'O', 15},
    {'P', 16},
    {'Q', 17},
    {'R', 18},
    {'S', 19},
    {'T', 20},
    {'U', 21},
    {'V', 22},
    {'W', 23},
    {'X', 24},
    {'Y', 25},
    {'Z', 26},
    {'a', 27},
    {'b', 28},
    {'c', 29},
    {'d', 30},
    {'e', 31},
    {'f', 32},
    {'g', 33},
    {'h', 34},
    {'i', 35},
    {'j', 36},
    {'k', 37},
    {'l', 38},
    {'m', 39},
    {'n', 40},
    {'o', 41},
    {'p', 42},
    {'q', 43},
    {'r', 44},
    {'s', 45},
    {'t', 46},
    {'u', 47},
    {'v', 48},
    {'w', 49},
    {'x', 50},
    {'y', 51},
    {'z', 52},
    {'1', 53},
    {'2', 54},
    {'3', 55},
    {'4', 56},
    {'5', 57},
    {'6', 58},
    {'7', 59},
    {'8', 60},
    {'9', 61},
    {'0', 62},
    {'.', 63},
    {'!', 64},
    {'?', 65},
    {':', 66},
    {';', 67},
    {',', 68},
    {'_', 69},
    {'/', 70},
    {'\\', 71},
    {'"', 72},
    {'\'', 73},
    {' ', 74},
    {'|', 75},
    {'@', 76},
    {'#', 77},
    {'$', 78},
    {'%', 79},
    {'^', 80},
    {'&', 81},
    {'*', 82},
    {'(', 83},
    {')', 84},
    {'-', 85},
    {'+', 86},
    {'=', 87},
    {'{', 88},
    {'}', 89},
    {'[', 90},
    {']', 91},
    {'`', 92},
    {'<', 93},
    {'>', 94},
    {'~', 95},
};

// Map for key to char.
inline std::map<Key, char> Key_To_Char_Map {
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

// Map for shifted key to char.
inline std::map<Key, char> ShiftedKey_To_Char_Map {
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
