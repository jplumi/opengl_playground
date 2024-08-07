#version 410 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoord;

out vec2 v_TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
    v_TexCoords = texCoord;
    gl_Position = u_Projection * u_View * u_Model * vec4(vertex, 0.0, 1.0);
}
