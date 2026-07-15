#pragma once

#include <cstdint>
#include <vector>

struct Vertex {
    float x, y, z;  // manages position
    float u, v;     // manages texture

    std::uint8_t tint_r = 255;
    std::uint8_t tint_g = 255;
    std::uint8_t tint_b = 255;
    std::uint8_t light_level = 6;
};

struct Primitive {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    void setRGBL(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t light);
    void appendPrimitive(Primitive& other_primitive);
    void clearPrimitive();
};

Primitive quad(
    const Vertex& vertex_a,
    const Vertex& vertex_b,
    const Vertex& vertex_c,
    const Vertex& vertex_d
);
