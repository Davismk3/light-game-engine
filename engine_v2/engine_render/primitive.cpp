#include "primitive.hpp"

Primitive quad(
    const Vertex& vertex_a,
    const Vertex& vertex_b,
    const Vertex& vertex_c,
    const Vertex& vertex_d
) {
    return {{vertex_a, vertex_b, vertex_c, vertex_d}, {0, 1, 2, 0, 2, 3}};  // vertices and indices
}
