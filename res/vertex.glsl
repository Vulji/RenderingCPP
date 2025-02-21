#version 410

layout(location = 0) in vec2 in_position;
uniform float aspect_ratio;
uniform float time_addition;
uniform mat4 view_projection_matrix;

void main()
{
    vec2 position = in_position;
    position += vec2(0.4f*time_addition,0.4f);

    gl_Position = view_projection_matrix * vec4(in_position, 0., 1.);
}