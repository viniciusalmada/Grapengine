#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;

out vec4 out_color;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
    gl_Position = (u_proj) * (u_view) * (u_model) * vec4(in_position, 1.0);
    out_color = in_color;
}
