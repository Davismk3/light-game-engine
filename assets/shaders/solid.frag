#version 330 core

out vec4 frag_color;

uniform vec3 u_tint;
uniform float u_opacity;

void main() {
    frag_color = vec4(u_tint, u_opacity);
}