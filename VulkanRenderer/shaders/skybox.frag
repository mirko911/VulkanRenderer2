#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable

layout (set = 0, binding = 0) uniform samplerCube samplerCubeMap[1];

layout (location = 0) in vec3 inUVW;
layout (location = 1) flat in int inSkyboxID;

layout (location = 0) out vec4 outFragColor;

void main() 
{
	outFragColor = texture(samplerCubeMap[inSkyboxID], inUVW);
}