#pragma once

#include "../engine_utility/vector.hpp"
#include "../engine_render/primitive.hpp"
#include "../engine_render/texture.hpp"
#include "../engine_config.hpp"

#include <string>
#include <iostream>
#include <map>

// Probably Move this into app/?

struct TextStyle {
    float size;
    Vector3F color;
    Vector3F backgroud_color = {0.0f, 0.0f, 0.0f};
    bool has_background;
    bool centered;  // the start position is now the center of the text display
    float opacity = 1.0f;
};

struct Text {
    Text() = default;
    Text(Vector2F start_position, TextStyle style, std::string string);

    Vector2F m_position;  // normalized to ([-1, 1], [-1, 1]) for screen
    TextStyle m_style;
    std::string m_string;

    Primitive buildPrimitives();
};

inline std::map<char, int> GlyphMap {
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

struct GlyphAtlasPositionUV {
    int u;
    int v;
};
