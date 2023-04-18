#version 450 core

layout(location = 0) in vec3 worldCoord;

//uniform mat4 view;


void main()
{
	gl_Position = vec4(worldCoord, 1.0);
}