#pragma once

#include "../engine_platform/button.hpp"
#include "../engine_platform/textbox.hpp"
#include "../engine_render/text.hpp"

#include <cstddef>

struct IndexStride {
    unsigned int first_index;  // starting index in primitives 
    unsigned int index_count;  // how many indices to use
};

class Menu {
    // The menu stores and renders buttons, text, and textboxes.
public:
    ~Menu() = default;
    
    void initialize();

    void buildMesh();
    void processInput(const Input& input);
    void draw();

    void shutdown();

    void addButton(Button button);
    void addText(Text text);
    void addTextBox(TextBox textbox);

    void resize(Matrix4F projection, float aspect);

    std::vector<Button> m_buttons;
    std::vector<Text> m_texts;
    std::vector<Text> m_textbox_texts;
    std::vector<TextBox> m_textboxes;

    std::array<std::vector<IndexStride>, 4> m_index_strides;

private:
    Mesh m_mesh;
    Shader m_shader;

    Texture m_font_texture;

    float m_aspect = 1.0f;

    bool m_mesh_dirty = true;
};
