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

void drawMeshRange(
    Mesh& mesh,
    Shader& shader,
    unsigned int first_index,
    unsigned int index_count
) {
    shader.shaderUse();
    glBindVertexArray(mesh.m_VAO);

    const std::size_t byte_offset = static_cast<std::size_t>(first_index) * sizeof(unsigned int);

    glDrawElements(
        GL_TRIANGLES,
        static_cast<GLsizei>(index_count),
        GL_UNSIGNED_INT,
        reinterpret_cast<const void*>(byte_offset)
    );

    glBindVertexArray(0);
}

void drawClear(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
