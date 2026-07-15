#include "primitive.hpp"

Primitive quad(
    const Vertex& vertex_a,
    const Vertex& vertex_b,
    const Vertex& vertex_c,
    const Vertex& vertex_d
) {
    return {{vertex_a, vertex_b, vertex_c, vertex_d}, {0, 1, 2, 0, 2, 3}};  // vertices and indices
}

void Primitive::setRGBL(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t light) {
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].tint_r = r;
        vertices[i].tint_g = g;
        vertices[i].tint_b = b;
        vertices[i].light_level = light;
    }
}

void Primitive::appendPrimitive(Primitive& other_primitive) {
    vertices.reserve(vertices.size() + other_primitive.vertices.size());
    vertices.insert(vertices.end(), other_primitive.vertices.begin(), other_primitive.vertices.end());

    indices.reserve(indices.size() + other_primitive.indices.size());
    const unsigned int base_index = static_cast<unsigned int>(vertices.size());
    for (unsigned int index : other_primitive.indices) indices.push_back(base_index + index);
}

void Primitive::clearPrimitive() {
    vertices.clear();
    indices.clear();
}
