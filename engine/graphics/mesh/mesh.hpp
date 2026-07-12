#pragma once

#include <stdexcept>
#include "graphics/primitive/primitive.hpp"

class Mesh {
public:
    //void meshInitialize(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh() = default;
    
    void meshClear();
    void meshAppend(const Primitive& primitive);
    void meshUpload();  // Upload To GPU
    void meshShutdown();

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    unsigned int m_EBO = 0;

private:

    // unsigned int m_draw_mode = GL_TRIANGLES;

};
