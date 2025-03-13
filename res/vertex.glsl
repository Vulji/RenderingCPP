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

vec3 apply_matrix_to_position(mat4 matrix, vec3 point) {
    vec4 tmp = matrix * vec4(point, 1.0);
    return tmp.xyz / tmp.w;
}

vec3 apply_matrix_to_direction(mat4 matrix, vec3 direction) {
    vec4 tmp = matrix * vec4(direction, 0.0);
    return normalize(tmp.xyz);
}

void main()
{
    //vec3 position = in_position;
    vertex_position = apply_matrix_to_position(model_matrix, in_position);
    normals = apply_matrix_to_direction(model_matrix, in_normal);
    uv = aTexCoord;
    
    mat4 model_view_projection_matrix =  view_projection_matrix * model_matrix;

    //gl_Position = model_view_projection_matrix * vec4(in_position, 1.);
    gl_Position = view_projection_matrix * vec4(vertex_position, 1.0);

}