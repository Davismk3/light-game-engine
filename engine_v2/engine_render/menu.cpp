#include "menu.hpp"

void Menu::initialize() {
    m_shader.shaderInitialize("engine_v2/engine_assets/basic.vert", "engine_v2/engine_assets/basic.frag");
    m_shader.shaderUse();
    m_font_texture.textureLoad("engine_v2/engine_assets/font.png");
}

void Menu::buildMesh() {
    m_mesh.meshClear();
    for (std::vector<IndexStride>& index_strides : m_index_strides) index_strides.clear();

    // Mesh Buttons
    for (Button& button : m_buttons) {
        Primitive primitive = button.buildPrimitives();
        IndexStride button_stride = {.first_index = static_cast<unsigned int>(m_mesh.m_indices.size()), .index_count = static_cast<unsigned int>(primitive.indices.size())};

        m_mesh.meshAppendPrimitives(primitive);
        m_index_strides[0].push_back(button_stride);
    }

    // Mesh Text
    for (Text& text : m_texts) {
        Primitive primitive = text.buildPrimitives();
        IndexStride text_stride = {.first_index = static_cast<unsigned int>(m_mesh.m_indices.size()), .index_count = static_cast<unsigned int>(primitive.indices.size())};

        m_mesh.meshAppendPrimitives(primitive);
        m_index_strides[1].push_back(text_stride);
    }

    // Mesh TextBoxes
    for (TextBox& textbox : m_textboxes) {
        Primitive box_primitive = textbox.buildBoxPrimitives();
        IndexStride box_stride = {.first_index = static_cast<unsigned int>(m_mesh.m_indices.size()), .index_count = static_cast<unsigned int>(box_primitive.indices.size())};

        m_mesh.meshAppendPrimitives(box_primitive);
        m_index_strides[2].push_back(box_stride);

        Primitive text_primitive = textbox.buildTextPrimitives();
        IndexStride textbox_text_stride = {.first_index = static_cast<unsigned int>(m_mesh.m_indices.size()), .index_count = static_cast<unsigned int>(text_primitive.indices.size())};

        m_mesh.meshAppendPrimitives(text_primitive);
        m_index_strides[3].push_back(textbox_text_stride);
    }

    m_mesh.meshUpload();
    m_mesh_dirty = false;
}

void Menu::processInput(const Input& input) {

    // Process Buttons
    for (std::size_t i = 0; i < m_buttons.size(); ++i) {
        Button& button = m_buttons[i];
        button.processInput(input, m_aspect);
    }

    // Process TextBoxes
    for (TextBox& textbox : m_textboxes) {

        textbox.processInput(input, m_aspect);
        if (textbox.m_text_changed) {
            m_mesh_dirty = true;
            //std::cout << "text added\n";
        }
    }
}

void Menu::draw() {
    if (m_mesh_dirty) buildMesh();
    m_shader.shaderUse();

    // Bind VAO
    glBindVertexArray(m_mesh.m_VAO);

    // Draw Buttons
    for (int i = 0; i < m_buttons.size(); i++) {
        const Button& button = m_buttons[i];
        const ButtonStyle& style = button.m_style;
        IndexStride& button_stride = m_index_strides[0][i];

        Vector3F color = style.idle_color;
        if (button.m_state == ButtonState::Held) color = style.held_color;
        else if (button.m_state == ButtonState::Hover) color = style.hover_color;

        m_shader.shaderSetVec3("u_tint", color.x, color.y, color.z);
        m_shader.shaderSetFloat("u_opacity", style.opacity);
        m_shader.shaderSetBool("use_texture", false);

        drawMeshRangeExposed(m_mesh, m_shader, button_stride.first_index, button_stride.index_count); 
    }

    // Draw Text
    m_font_texture.textureBind();
    for (int i = 0; i < m_texts.size(); i++) {
        Text& text = m_texts[i];
        TextStyle& style = text.m_style;
        Vector3F color = style.color;
        IndexStride& text_stride = m_index_strides[1][i];

        m_shader.shaderSetFloat("u_opacity", style.opacity);
        m_shader.shaderSetBool("use_texture", true);

        // Background Text
        if (text.m_style.has_background) {
            Vector3F background_color = style.backgroud_color;
            // -
            m_shader.shaderSetVec3("u_tint", background_color.x, background_color.y, background_color.z);
            m_shader.shaderSetVec3("a_shift", style.size / static_cast<float>(GLYPH_HEIGHT), -style.size / static_cast<float>(GLYPH_HEIGHT), 0.0f);
            // - 
            drawMeshRangeExposed(m_mesh, m_shader, text_stride.first_index, text_stride.index_count);
        }

        // Foreground Text
        m_shader.shaderSetVec3("a_shift", 0.0f, 0.0f, 0.0f);
        m_shader.shaderSetVec3("u_tint", color.x, color.y, color.z);
        // - 
        drawMeshRangeExposed(m_mesh, m_shader, text_stride.first_index, text_stride.index_count);

        //text_index += index_count;
    }

    // Draw TextBoxes
    for (int i = 0; i < m_textboxes.size(); i++) {
        TextBox& textbox = m_textboxes[i];
        TextBoxStyle& style = textbox.m_style;
        Vector3F box_color = style.idle_color;
        Vector3F text_color = textbox.m_combined_current_text.m_style.color;
        IndexStride& box_stride = m_index_strides[2][i];
        IndexStride& text_stride = m_index_strides[3][i];
        
        // Draw Box
        m_shader.shaderSetBool("use_texture", false);
        m_shader.shaderSetFloat("u_opacity", style.opacity);
        m_shader.shaderSetVec3("u_tint", box_color.x, box_color.y, box_color.z);

        drawMeshRangeExposed(m_mesh, m_shader, box_stride.first_index, box_stride.index_count);

        // Draw Text
        m_shader.shaderSetBool("use_texture", true);
        m_shader.shaderSetVec3("u_tint", text_color.x, text_color.y, text_color.z);
        m_shader.shaderSetFloat("u_opacity", textbox.m_combined_current_text.m_style.opacity);
        drawMeshRangeExposed(m_mesh, m_shader, text_stride.first_index, text_stride.index_count);

    }

    // Unbind VAO
    glBindVertexArray(0);
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

void Menu::addTextBox(TextBox textbox) {
    m_textboxes.push_back(textbox);
    m_mesh_dirty = true;
}

void Menu::resize(Matrix4F projection, float aspect) {
    m_shader.shaderUse();
    m_shader.shaderSetMat4("u_projection", projection); 

    float aspect_ratio = aspect / m_aspect;

    for (Button& button : m_buttons) {
        button.m_bounds.width *= aspect_ratio;
        button.m_position.u *= aspect_ratio;
    }

    m_aspect = aspect;
    m_mesh_dirty = true;
}
