#pragma once

#include "text.hpp"
#include "panel.hpp"
#include "button.hpp"

#include <cstddef>
#include <optional>

struct MenuQuad {
    Primitive quad_primitive;
    float opacity = 1.0f;
    Vector3F tint = {1.0f, 1.0f, 1.0f};
    bool follows_cursor = false;
};

struct IndexStride {
    unsigned int first_index;  // starting index in primitives 
    unsigned int index_count;  // how many indices to use
};

// Menu object. This stores and renders buttons, text, and other menu related objects.
class Menu {
public:
    ~Menu() = default;
    void initialize(Texture* p_texture_ = nullptr);
    void buildMesh();
    void processInput(const Input& input);
    void draw();
    void update(float delta_time);
    void resize(Matrix4F projection, float aspect);
    void shutdown();

    void addButton(Button button);
    void addTexturedButton(TexturedButton button);
    void addText(Text text);
    void addTextBox(TextBox textbox);
    void addBasicQuad(MenuQuad menu_quad);
    void addTextureQuad(MenuQuad menu_quad);
    void addPanel(Panel panel);

    // Objects
    std::vector<Button>         m_buttons;
    std::vector<TexturedButton> m_texture_buttons;
    std::vector<Text>           m_texts;
    std::vector<TextBox>        m_textboxes;
    std::vector<MenuQuad>       m_basic_quads;
    std::vector<MenuQuad>       m_texture_quads;
    std::vector<Panel>          m_panels;

    std::array<std::vector<IndexStride>, 9> m_index_strides;
    bool m_mesh_dirty = true;

private:
    Mesh m_mesh;
    Shader m_shader;

    Texture* p_texture = nullptr;
    Texture m_font_texture;

    float m_time = 0.0f;
    float m_cursor_flash_time = 0.25f;
    float m_aspect = 1.0f;
    bool m_cursor_toggle_bool = false;
    float m_mouse_u = 0.0f;
    float m_mouse_v = 0.0f;
};
