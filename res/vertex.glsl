#version 410

layout(location = 0) in vec3 in_position;
uniform float aspect_ratio;
uniform float time_addition;
uniform mat4 view_projection_matrix;
uniform mat4 model_matrix;

void main()
{
    vec3 position = in_position;

    mat4 model_view_projection_matrix =  view_projection_matrix *model_matrix;

    gl_Position = model_view_projection_matrix * vec4(in_position, 1.);
}