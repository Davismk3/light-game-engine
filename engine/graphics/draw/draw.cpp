#include "draw.hpp"
#include <glad/gl.h>

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

void drawClear(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
}
