#pragma once

#include "primitive.hpp"

#include <stdexcept>
#include <stdexcept>
#include <glad/gl.h>

class Mesh {
public:
    ~Mesh();
    
    void meshClear();
    void meshAppendPrimitives(const Primitive& primitive);
    // also add a meshAppendMesh() for combining meshes?
    void meshUpload();  // Upload To GPU
    void meshShutdown();

    Primitive meshGetPrimitives();

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
