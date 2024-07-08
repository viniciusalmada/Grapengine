#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;

out vec4 out_color;

uniform float width;
uniform float height;

void main()
{
    gl_Position = vec4(
                    in_position.x / (width/2) - 1.0,
                    -(in_position.y / (height/2) - 1.0),
                    in_position.z,
                    1.0);
    out_color = in_color;
}
