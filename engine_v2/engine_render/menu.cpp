#include "menu.hpp"

void Menu::initialize() {
    m_shader.shaderInitialize("engine_v2/engine_assets/basic.vert", "engine_v2/engine_assets/basic.frag");
    m_shader.shaderUse();
    m_font_texture.textureLoad("engine_v2/engine_assets/font.png");
}

void Menu::buildMesh() {
    m_mesh.meshClear();

    for (std::size_t i = 0; i < m_buttons.size(); ++i) {

        // perhaps add the build primitive logic to button.cpp like how text.cpp handles it?
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

    // for loop for appending text primitives 
    for (int i = 0; i < m_texts.size(); i++) {
        Text text = m_texts[i];
        Primitive primitive = text.buildPrimitives();
        m_mesh.meshAppendPrimitives(primitive);
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
        m_shader.shaderSetBool("use_texture", false);

        drawMeshRange(m_mesh, m_shader, static_cast<unsigned int>(i) * 6, 6);  // note this inefficiently binds and unbinds for each button
    }   

    m_shader.shaderUse();
    m_font_texture.textureBind();
    unsigned int text_index = static_cast<unsigned int>(m_buttons.size()) * 6;
    // text draw loop 
    for (int i = 0; i < m_texts.size(); i++) {
        Text& text = m_texts[i];
        TextStyle& style = text.m_style;
        Vector3F color = style.color;
        unsigned int index_count = static_cast<unsigned int>(text.m_string.size()) * 6;

        m_shader.shaderSetFloat("u_opacity", style.opacity);
        m_shader.shaderSetBool("use_texture", true);

        // Background Text
        if (text.m_style.has_background) {
            Vector3F background_color = style.backgroud_color;
            // -
            m_shader.shaderSetVec3("u_tint", background_color.x, background_color.y, background_color.z);
            m_shader.shaderSetVec3("a_shift", style.size * 0.1f, -style.size * 0.025f, 0.0f);
            // - 
            drawMeshRange(m_mesh, m_shader, text_index, index_count);
        }

        // Foreground Text
        m_shader.shaderSetVec3("a_shift", 0.0f, 0.0f, 0.0f);
        m_shader.shaderSetVec3("u_tint", color.x, color.y, color.z);
        // - 
        drawMeshRange(m_mesh, m_shader, text_index, index_count);

        text_index += index_count;
    }
}

void Menu::shutdown() {

}

void Menu::addButton(Button button) {
    m_buttons.push_back(button);
    m_mesh_dirty = true;
}

void Menu::addText(Text text) {
    m_texts.push_back(text);
    m_mesh_dirty = true;
}
