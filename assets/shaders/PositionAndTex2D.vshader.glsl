#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texture_coord;

out vec2 out_texture_coords;

uniform mat4 u_model;
//uniform mat4 u_view;
//uniform mat4 u_proj;
uniform mat4 u_VP;

void main()
{
    gl_Position = (u_VP) * vec4(in_position, 1.0);
    out_texture_coords = in_texture_coord;
}