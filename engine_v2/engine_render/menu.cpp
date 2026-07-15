#include "menu.hpp"

void Menu::initialize() {
    m_shader.shaderInitialize("engine_v2/engine_assets/basic.vert", "engine_v2/engine_assets/basic.frag");
    m_shader.shaderUse();
}

void Menu::buildMesh() {
    m_mesh.meshClear();

    for (std::size_t i = 0; i < m_buttons.size(); ++i) {

        const float left = m_buttons[i].m_bounds.u - m_buttons[i].m_bounds.width;
        const float right = m_buttons[i].m_bounds.u + m_buttons[i].m_bounds.width;
        const float bottom = m_buttons[i].m_bounds.v - m_buttons[i].m_bounds.height;
        const float top = m_buttons[i].m_bounds.v + m_buttons[i].m_bounds.height;

        m_mesh.meshAppendPrimitives(quad(
            {right, top, 0.0f, 1.0f, 1.0f},
            {right, bottom, 0.0f, 1.0f, 0.0f},
            {left, bottom, 0.0f, 0.0f, 0.0f},
            {left, top, 0.0f, 0.0f, 1.0f}
        ));
    }
    m_mesh.meshUpload();
    m_mesh_dirty = false;
}

void Menu::processInput(const Input& input) {
    for (std::size_t i = 0; i < m_buttons.size(); ++i) {
        Button& button = m_buttons[i];
        button.update(input);

        // since Menu has m_buttons, button press detection can occur outside this class
        if (button.m_state == ButtonState::Held) {

        } else if (button.m_state == ButtonState::Hover) {

        }
    }
}

void Menu::draw() {
    if (m_mesh_dirty) buildMesh();
    m_shader.shaderUse();

    for (int i = 0; i < m_buttons.size(); i++) {
        const Button& button = m_buttons[i];
        const ButtonStyle& style = button.m_style;

        Vector3F color = style.idle_color;
        if (button.m_state == ButtonState::Held) color = style.held_color;
        else if (button.m_state == ButtonState::Hover) color = style.hover_color;

        m_shader.shaderSetVec3("u_tint", color.x, color.y, color.z);
        m_shader.shaderSetFloat("u_opacity", style.opacity);

        drawMeshRange(m_mesh, m_shader, static_cast<unsigned int>(i) * 6, 6);  // note this inefficiently binds and unbinds for each button
    }
}

void Menu::shutdown() {

}

void Menu::addButton(ButtonBounds bounds, ButtonStyle style) {
    Button button(bounds, style);
    m_buttons.push_back(button);
    m_mesh_dirty = true;
}
