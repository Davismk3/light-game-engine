#include "draw.hpp"

void drawMesh(Mesh& mesh, Shader& shader) {
    unsigned int vertex_count = static_cast<unsigned int>(mesh.m_vertices.size());
    unsigned int index_count  = static_cast<unsigned int>(mesh.m_indices.size());
    
    shader.shaderUse();
    
    // Bind VAO
    glBindVertexArray(mesh.m_VAO);

    // Draw
    if (index_count > 0) glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
    else glDrawArrays(GL_TRIANGLES, 0, vertex_count);

    // Unbind VAO
    glBindVertexArray(0);
}

// Separate Draw Calls On Single Mesh, Allows For Local Shader Differences Within Single Mesh
void drawMeshRange(
    Mesh& mesh,
    Shader& shader,
    unsigned int first_index,
    unsigned int index_count
) {
    shader.shaderUse();

    // Bind VAO
    glBindVertexArray(mesh.m_VAO);

    // Draw
    const std::size_t byte_offset = static_cast<std::size_t>(first_index) * sizeof(unsigned int);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index_count), GL_UNSIGNED_INT, reinterpret_cast<const void*>(byte_offset));

    // Unbind VAO
    glBindVertexArray(0);
}

void drawMeshRangeEfficient(
    Mesh& mesh,
    Shader& shader,
    unsigned int index_size,
    unsigned int index_count
) {
    shader.shaderUse();

    // Bind VAO
    glBindVertexArray(mesh.m_VAO);

    for (int i = 0; i < index_size; i++) {
        const std::size_t byte_offset = static_cast<std::size_t>(static_cast<unsigned int>(i) * 6) * sizeof(unsigned int);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index_count), GL_UNSIGNED_INT, reinterpret_cast<const void*>(byte_offset));
    }

    // Unbind VAO
    glBindVertexArray(0);
}

void drawMeshRangeExposed(
    Mesh& mesh,
    Shader& shader,
    unsigned int first_index,
    unsigned int index_count
) {

    // Draw
    const std::size_t byte_offset = static_cast<std::size_t>(first_index) * sizeof(unsigned int);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index_count), GL_UNSIGNED_INT, reinterpret_cast<const void*>(byte_offset));
}

void drawClear(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
