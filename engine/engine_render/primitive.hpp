#pragma once

#include <cstdint>
#include <vector>

struct Vertex {
    float x, y, z;  // manages position
    float u, v;     // manages texture

    std::uint8_t artificial_r = 255;  // artificial red tint 
    std::uint8_t artificial_g = 255;  // artificial green tint
    std::uint8_t artificial_b = 255;  // artificial blue tint 
};

struct Primitive {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;  

    void setArtificialRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b);
    void appendPrimitive(const Primitive& other_primitive);
    void clearPrimitive();
};

Primitive quad(
    const Vertex& vertex_a,
    const Vertex& vertex_b,
    const Vertex& vertex_c,
    const Vertex& vertex_d
);
