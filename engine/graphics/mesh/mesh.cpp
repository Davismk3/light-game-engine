#include <stdexcept>
#include <glad/gl.h>
#include "mesh.hpp"
#include <vector>

void Mesh::meshClear() {
    m_vertices.clear();
    m_indices.clear();
}

void Mesh::meshAppend(const Primitive& primitive) {
    unsigned int base_index = static_cast<unsigned int>(m_vertices.size());
    
    for (const Vertex& vertex : primitive.vertices) m_vertices.push_back(vertex);
    for (const int index : primitive.indices) m_indices.push_back(base_index + index);
}

void Mesh::meshUpload() {
    meshShutdown();  // Avoid Memory Leak

    unsigned int vertex_count = static_cast<unsigned int>(m_vertices.size());
    unsigned int index_count  = static_cast<unsigned int>(m_indices.size());

    // Vertex Array Object
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO); 

    // Buffer Objects
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
    if (index_count > 0) {
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
    }

    // Position (x,y,z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture (u,v)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::meshShutdown() {
    if (m_VAO != 0) glDeleteVertexArrays(1, &m_VAO); m_VAO = 0;
    if (m_VBO != 0) glDeleteBuffers(1, &m_VBO); m_VBO = 0;
    if (m_EBO != 0) glDeleteBuffers(1, &m_EBO); m_EBO = 0;
}
