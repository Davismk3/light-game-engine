#pragma once

#include "../engine_platform/button.hpp"
#include "../engine_render/text.hpp"

#include <cstddef>

class Menu {
public:
    ~Menu() = default;
    
    void initialize();

    void buildMesh();
    void processInput(const Input& input);
    void draw();

    void shutdown();

    void addButton(Button button);
    void addText(Text text);

    std::vector<Button> m_buttons;
    std::vector<Text> m_texts;

private:
    Mesh m_mesh;
    Shader m_shader;

    Texture m_font_texture;

    bool m_mesh_dirty = true;
};
