#version 330 core

out vec4 frag_color;
in vec2 v_uv;

// Uniforms 
uniform sampler2D u_texture;
uniform vec3 u_tint = vec3(1.0, 1.0, 1.0);  // baseline is no tint
uniform float u_light = 1.0;                // baseline is fully illuminated 
uniform float u_opacity = 1.0;              // baseline is fully opaque
uniform float u_alpha_cutoff = 0.0;         // baseline is no alpha cutoff

void main() {
    vec4 color = texture(u_texture, v_uv);

    if (color.a < u_alpha_cutoff) discard;

    color.rgb *= u_tint;
    color.rgb *= u_light;
    color.a *= u_opacity;

    frag_color = color;
}
