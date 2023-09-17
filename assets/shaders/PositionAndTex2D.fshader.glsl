#version 330 core

in vec2 out_texture_coords;

out vec4 fragColor;

uniform sampler2D dice_texture;

void main()
{
    fragColor = texture2D(dice_texture, out_texture_coords);
}