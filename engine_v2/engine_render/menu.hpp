#pragma once

#include "../engine_platform/button.hpp"

class Menu {
public:
    ~Menu() = default;
    
    void initialize();

    void buildMesh();
    void processInput(const Input& input);
    void draw();

    void shutdown();

    void addButton(ButtonBounds bounds, ButtonStyle style);

    std::vector<Button> m_buttons;

private:
    Mesh m_mesh;
    Shader m_shader;

    bool m_mesh_dirty = true;
};

/*
collection of buttons
    shared mesh
    shared shader
    mesh construction/upload
    drawing*/