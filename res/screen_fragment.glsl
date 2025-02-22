#version 410

out vec4 out_color;
in vec2 uv;

uniform sampler2D my_texture;

void main() {
    vec4 tex_color = texture(my_texture, uv);
    out_color = vec4(tex_color.r, 0.0, 0.0, tex_color.a);
}
