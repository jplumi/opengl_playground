#version 410 core

in vec2 v_TexCoords;

out vec4 FragColor;

uniform vec3 color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoords);
    FragColor = texColor;
}
