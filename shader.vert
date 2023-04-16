#version 450 core

layout(location = 0) in vec3 worldCoord;

void main()
{
	gl_Position = vec4(worldCoord.x, worldCoord.y, worldCoord.z, 1.0);
}