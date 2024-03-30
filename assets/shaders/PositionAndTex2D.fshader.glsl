#version 330 core

in vec2 out_texture_coords;
in vec4 out_color;
in vec3 out_normal;
in vec3 out_frag_pos;

out vec4 fragColor;

uniform sampler2D u_texture;

uniform vec3 u_lightPos;
uniform vec3 u_ambientColor;
uniform float u_ambientStrength;

void main()
{
  vec3 norm = normalize(out_normal);
  vec3 light_dir = normalize(u_lightPos - out_frag_pos);
  float diff = max(dot(norm, light_dir), 0);
  vec3 diffuse = diff * vec3(1, 1, 1);

  vec3 ambient = u_ambientStrength * u_ambientColor;

  vec3 object_color = (texture2D(u_texture, out_texture_coords) * out_color).rgb;
  vec3 result = (ambient + diffuse) * object_color;
  fragColor = vec4(result, out_color.a);
}