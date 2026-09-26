#pragma once

#include "../engine_platform/input.hpp"
#include "../engine_utility/vector.hpp"
#include "../engine_render/mesh.hpp"
#include "../engine_render/shader.hpp"
#include "../engine_render/draw.hpp"

#include <iostream>

// State of the button.
enum class ButtonState {
    Idle, 
    Hover,
    Held,
    Activated
};

// Configurations for the button colors, height/width, and opacity.
struct ButtonConfig {
    float height;
    float width;
    Vector3F held_color;
    Vector3F hover_color;
    Vector3F idle_color;
    float opacity = 1.0f;
};

// Texture button size presets.
enum class TexturedButtonType {
    Square,
    Small,
    Large,
};

// Button object.
class Button {
public: 
    Button() = default;
    Button(Vector2F position, ButtonConfig config);

    Primitive buildPrimitives();
    
    ButtonState m_state = ButtonState::Idle;
    Vector2F m_position;
    ButtonConfig m_config;

    bool isHover(const Input& input, float aspect);  // Is the user's mouse hovering over this button?
    bool isHeld(const Input& input, float aspect);  // Is the user's mouse holding this button?
    bool isReleased(const Input& input, float aspect);  // Did the user's mouse release this button?
    void processInput(const Input& input, float aspect);
};

// Textured button object.
class TexturedButton : public Button {
public: 
    TexturedButton() = default;
    TexturedButton(Vector2F position, ButtonConfig style, TexturedButtonType type, float size);

    Primitive buildPrimitives();

    TexturedButtonType m_type;
    float m_size;  // This overwrites the inherited height/width inside ButtonConfig.
};
