#include "primitive.hpp"

Primitive quad(
    const Vertex& vertex_a,
    const Vertex& vertex_b,
    const Vertex& vertex_c,
    const Vertex& vertex_d
) {
    return {{vertex_a, vertex_b, vertex_c, vertex_d}, {0, 1, 2, 0, 2, 3}};  // vertices and indices
}

void Primitive::setArtificialRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].artificial_r = r;
        vertices[i].artificial_g = g;
        vertices[i].artificial_b = b;
    }
}

void Primitive::appendPrimitive(const Primitive& other) {
    const unsigned int base_index = static_cast<unsigned int>(vertices.size());

    vertices.insert(vertices.end(), other.vertices.begin(), other.vertices.end());

    for (unsigned int index : other.indices) indices.push_back(base_index + index);
}

void Primitive::clearPrimitive() {
    vertices.clear();
    indices.clear();
}
