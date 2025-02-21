#version 410

out vec4 out_color;


in vec3 vertex_position;

void main()
{
    //out_color = vec4(1.0, 0.85, 0.0, 1.0);
    //out_color = vec4(uv.x, uv.y, 0., 1.);. 
    out_color = vec4(vertex_position, 1.);
}