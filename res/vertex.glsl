#version 410

layout(location = 0) in vec3 in_position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 in_normal;
uniform float aspect_ratio;
uniform float time_addition;
uniform mat4 view_projection_matrix;
uniform mat4 model_matrix;

out vec3 vertex_position;
out vec3 normals;
out vec2 uv;

void main()
{
    //vec3 position = in_position;
    vertex_position = in_position;
    normals = in_normal;
    uv = aTexCoord;
    
    mat4 model_view_projection_matrix =  view_projection_matrix * model_matrix;

    gl_Position = model_view_projection_matrix * vec4(in_position, 1.);
}