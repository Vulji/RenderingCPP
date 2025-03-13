#version 410

out vec4 out_color;
out vec4 texture_color;


in vec3 vertex_position;
in vec3 normals;
in vec2 uv;

uniform sampler2D my_texture;



void main()
{
vec3 normalized_normals = normalize(normals);

const vec3 light_direction = normalize(vec3(0.2, 0.3, -1.0));

float dotProd = dot(normalized_normals, light_direction);

vec4 texture_color = texture(my_texture, uv);

vec3 diffuse = texture_color.rgb * dotProd;

out_color = vec4(diffuse, texture_color.a);
}