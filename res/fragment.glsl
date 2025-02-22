#version 410

out vec4 out_color;
out vec4 texture_color;


in vec3 vertex_position;
in vec2 uv;

uniform sampler2D my_texture;

void main()
{
    //out_color = vec4(uv.x, uv.y, 0., 1.);
    texture_color = texture(my_texture, uv);
}