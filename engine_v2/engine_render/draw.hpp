#pragma once 

#include "mesh.hpp"
#include "shader.hpp"

void drawMesh(Mesh& mesh, Shader& shader);
void drawMeshRange(Mesh& mesh, Shader& shader, unsigned int first_index, unsigned int index_count);
void drawClear(float red, float green, float blue, float alpha);
