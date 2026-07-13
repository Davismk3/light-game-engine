#pragma once

#include "primitive.hpp"

#include <stdexcept>
#include <stdexcept>
#include <glad/gl.h>

class Mesh {
public:
    ~Mesh();
    
    void meshClear();
    void meshAppend(const Primitive& primitive);
    void meshUpload();  // Upload To GPU
    void meshShutdown();

    /*
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;
    */

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    unsigned int m_EBO = 0;

private:

    // unsigned int m_draw_mode = GL_TRIANGLES;

};
