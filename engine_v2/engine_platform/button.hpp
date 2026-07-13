#pragma once

#include "input.hpp"
#include "../engine_core/vector.hpp"
#include "../engine_render/mesh.hpp"
#include "../engine_render/shader.hpp"
#include "../engine_render/draw.hpp"

#include <iostream>

enum class ButtonState {
    Idle, 
    Hover,
    Held
};

struct ButtonBounds {
    float u;
    float v;
    float width;
    float height;
};

struct ButtonStyle {
    Vector3F idle_color;
    Vector3F hover_color;
    Vector3F held_color;
    float opacity = 1.0f;
};

class Button {
public: 
    Button(ButtonBounds bounds, ButtonStyle style);

    ButtonBounds m_bounds;
    ButtonStyle m_style;

    bool isHover(const Input& input);
    bool isHeld(const Input& input);

    void update(const Input& input);

    ButtonState m_state = ButtonState::Idle;
};
