#pragma once

#include "../engine_config.hpp"
#include "../engine_utility/vector.hpp"
#include "../engine_render/primitive.hpp"

/*
panel is a bunch of textured quads organized to form a display panel, like an inventory or hotbar backdrop.
*/

struct PanelConfig {
    float pixel_size = 1.0f;
    float width = 0.1f;
    float height = 0.1f;
    Vector2F center_position = {0.0f, 0.0f};
    float opacity = 1.0f;
    Vector3F tint = {1.0f, 1.0f, 1.0f};
    bool follows_cursor = false;
    bool inverted = false;
};

struct Panel {
    Primitive buildPrimitives();
    PanelConfig m_panel_config;
};
