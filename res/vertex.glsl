#version 410

layout(location = 0) in vec2 in_position;
float aspect_ratio;

void main()
{
    vec2 position = in_position;
    position += vec2(0.4f,0.4f);

    gl_Position = vec4(position, 0., 1.);
}