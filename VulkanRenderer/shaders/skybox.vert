#version 460
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inTangent;
layout(location = 3) in vec3 inBitangent;
layout(location = 4) in vec2 inUV;
layout(location = 5) in vec3 inColor;

layout (set = 0, binding = 1) uniform DynUBO {
	mat4 viewProj;
	int skyboxID;
} uboDyn;

layout (location = 0) out vec3 outUVW;
layout (location = 1) flat out int outSkyboxID;

out gl_PerVertex 
{
	vec4 gl_Position;
};

void main() 
{
	outUVW = inPosition;
	//outUVW.z *= -1.0;
	outUVW.y *= -1.0;
	//outUVW.z *= -1.0;
	gl_Position = uboDyn.viewProj * vec4(inPosition.xyz, 1.0);
	outSkyboxID = uboDyn.skyboxID;
}