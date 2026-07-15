#version 330 core

out vec4 frag_color;

in vec2 v_uv;
in vec3 v_tint;
flat in uint v_light_level;

// Uniforms 
uniform bool use_texture = false;           // true if use texture, false if solid color;
uniform sampler2D u_texture;                // the texture
uniform vec3 u_tint = vec3(1.0, 1.0, 1.0);  // baseline is no tint
uniform float u_light = 1.0;                // baseline is fully illuminated 
uniform float u_opacity = 1.0;              // baseline is fully opaque
uniform float u_alpha_cutoff = 0.0;         // baseline is no alpha cutoff

// Light Level -> Actual Light Value
float lightBrightness(uint level) {
    if (level <= 1u) return 0.20;
    if (level == 2u) return 0.32;
    if (level == 3u) return 0.45;
    if (level == 4u) return 0.60;
    if (level == 5u) return 0.78;
    return 1.00;
}

void main() {
    vec4 color;

    if (use_texture) {
        color = texture(u_texture, v_uv);
    } else {
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }

    if (color.a < u_alpha_cutoff) discard;

    // Shader Values 
    color.rgb *= u_tint;
    color.rgb *= u_light;
    color.a *= u_opacity;

    // Vertex Values 
    color.rgb *= v_tint;
    color.rgb *= lightBrightness(v_light_level);

    frag_color = color;
}
