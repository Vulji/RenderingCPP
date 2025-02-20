#version 410

layout(location = 0) in vec2 in_position;
uniform float aspect_ratio;
uniform float time_addition;

void main()
{
    vec2 position = in_position;
    position += vec2(0.4f*time_addition,0.4f);

    gl_Position = vec4(position.x/aspect_ratio,position.y, 0., 1.);
}