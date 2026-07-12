#pragma once 

#include "engine/graphics/mesh/mesh.hpp"
#include "engine/graphics/shader/shader.hpp"

void drawMesh(Mesh& mesh, Shader& shader);
void drawClear(float red, float green, float blue, float alpha);