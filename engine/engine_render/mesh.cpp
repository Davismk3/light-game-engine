#include "mesh.hpp"

Mesh::Mesh(Mesh&& other) noexcept
    : m_vertices(std::move(other.m_vertices)),
      m_indices(std::move(other.m_indices)),
      m_VAO(std::exchange(other.m_VAO, 0)),
      m_VBO(std::exchange(other.m_VBO, 0)),
      m_EBO(std::exchange(other.m_EBO, 0)) {
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    meshShutdown();

    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);

    m_VAO = std::exchange(other.m_VAO, 0);
    m_VBO = std::exchange(other.m_VBO, 0);
    m_EBO = std::exchange(other.m_EBO, 0);

    return *this;
}

void Mesh::meshClear() {
    m_vertices.clear();
    m_indices.clear();
}

void Mesh::meshAppendPrimitives(const Primitive& primitive) {
    unsigned int base_index = static_cast<unsigned int>(m_vertices.size());
    
    for (const Vertex& vertex : primitive.vertices) m_vertices.push_back(vertex);
    for (const int index : primitive.indices) m_indices.push_back(base_index + index);
}

Primitive Mesh::meshGetPrimitives() {
    return Primitive{m_vertices, m_indices };
}

void Mesh::meshUpload() {
    meshShutdown();  // Avoid Memory Leak

    m_vertex_count = static_cast<unsigned int>(m_vertices.size());
    m_index_count  = static_cast<unsigned int>(m_indices.size());

    // Vertex Array Object
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO); 

    // Buffer Objects
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_count * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
    if (m_index_count > 0) {
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_count * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
    }

    // ---

    // This is how the CPU tells the Shader/GPU what the vertex values are:

    // Position (x,y,z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture (u,v)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Artificial RGB (r,g,b)
    glVertexAttribIPointer(2, 3, GL_UNSIGNED_BYTE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, artificial_r)));
    glEnableVertexAttribArray(2);

    // ---

    // Clear CPU
    std::vector<Vertex>().swap(m_vertices);  // swap for empty 
    std::vector<unsigned int>().swap(m_indices);  // swap for empty 

    glBindVertexArray(0);
}

void Mesh::meshShutdown() {
    if (m_VAO != 0) glDeleteVertexArrays(1, &m_VAO); m_VAO = 0;
    if (m_VBO != 0) glDeleteBuffers(1, &m_VBO); m_VBO = 0;
    if (m_EBO != 0) glDeleteBuffers(1, &m_EBO); m_EBO = 0;
}

Mesh::~Mesh() {
    meshShutdown();
}
