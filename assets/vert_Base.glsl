#version 410 core

layout (location = 0) in vec2 vertex;
layout (location = 2) in vec3 color;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

out vec3 v_Color;

void main()
{
    v_Color = color;
    gl_Position = u_Projection * u_View * u_Model * vec4(vertex, 0.0, 1.0);
}
