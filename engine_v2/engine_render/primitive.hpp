#pragma once

#include <vector>

struct Vertex {
    float x;
    float y;
    float z;

    float u;
    float v;
};

struct Primitive {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

Primitive quad(
    const Vertex& vertex_a,
    const Vertex& vertex_b,
    const Vertex& vertex_c,
    const Vertex& vertex_d
);
