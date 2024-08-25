#version 400 core

#define MAX_LIGHTS 10
#define MAX_TEXTURES 16
#define WHITE_V3 vec3(1, 1, 1)

in vec2 out_texture_coords;
in vec4 out_color;
in vec3 out_normal;
in vec3 out_frag_pos;
flat in int out_tex_id;

out vec4 fragColor;

uniform sampler2D u_textures[MAX_TEXTURES];

uniform vec3 u_ambientColor;
uniform float u_ambientStrength;

uniform vec3 u_lightPos[MAX_LIGHTS];
uniform vec3 u_lightColor[MAX_LIGHTS];
uniform float u_lightStrength[MAX_LIGHTS];
uniform float u_specularStrenght[MAX_LIGHTS];
uniform float u_specularShininess[MAX_LIGHTS];

uniform int u_lights_count;

uniform vec3 u_viewPos;

vec3 get_ambient()
{
  vec3 ambient = u_ambientStrength * u_ambientColor;
  return ambient;
}

vec3 get_diffuse(inout vec3 frag_normal, inout vec3 light_directions[MAX_LIGHTS])
{
  // Calculate ray inclination
  vec3 diffuses = vec3(0, 0, 0);
  for (int i = 0; i < u_lights_count; i++)
  {
    float cosine = dot(frag_normal, light_directions[i]);// -1 to 1
    float diff = max(0, cosine);
    float dist_inv = 1 / distance(out_frag_pos, u_lightPos[i]);
    diffuses = diffuses + (dist_inv * u_lightStrength[i] * diff * u_lightColor[i]);
  }
  return diffuses;
}

vec3 get_specular(inout vec3 frag_normal, inout vec3 light_directions[MAX_LIGHTS])
{
  vec3 view_direction = normalize(u_viewPos - out_frag_pos);
  vec3 speculars = vec3(0, 0, 0);
  for (int i = 0; i < u_lights_count; i++)
  {
    vec3 reflect_dir = reflect(-light_directions[i], frag_normal);
    float spec = pow(max(dot(view_direction, reflect_dir), 0.0), u_specularShininess[i]);
    speculars = speculars + u_specularStrenght[i] * spec * u_lightColor[i];
  }
  return speculars;
}

void main()
{
  // Get fragment normal
  vec3 frag_normal = normalize(out_normal);

  // Calculate ray direction
  vec3 light_directions[MAX_LIGHTS];
  for (int i = 0; i < u_lights_count; i++)
  {
    light_directions[i] = normalize(u_lightPos[i] - out_frag_pos);
  }

  vec4 texture = texture2D(u_textures[out_tex_id], out_texture_coords);
  vec3 object_color = out_color.rgb * texture.rgb;
  vec3 result = (get_ambient() + get_diffuse(frag_normal, light_directions) + get_specular(frag_normal, light_directions)) * object_color;
  fragColor = vec4(result, out_color.a);
}