#version 330 core

out vec4 frag_color;
in vec2 v_uv;

// Uniforms 
uniform bool use_texture = false;           // true if use texture, false if solid color;
uniform sampler2D u_texture;                // the texture
uniform vec3 u_tint = vec3(1.0, 1.0, 1.0);  // baseline is no tint
uniform float u_light = 1.0;                // baseline is fully illuminated 
uniform float u_opacity = 1.0;              // baseline is fully opaque
uniform float u_alpha_cutoff = 0.0;         // baseline is no alpha cutoff

void main() {
    vec4 color;

    if (use_texture) {
        color = texture(u_texture, v_uv);
    } else {
        color = vec4(u_tint, u_opacity);
    }

    if (color.a < u_alpha_cutoff) discard;

    color.rgb *= u_tint;
    color.rgb *= u_light;
    color.a *= u_opacity;

    frag_color = color;
}
