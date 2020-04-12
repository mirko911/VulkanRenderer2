#version 460
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 outUV;

layout(set = 0, binding = 1) uniform UBO{
	mat4 projection;
	mat4 view;
    mat4 viewProj;
    vec4 position;
} ubo;

layout(set = 0, binding = 2) uniform UBODyn{
	mat4 modelMat;
} ubodyn;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inTangent;
layout(location = 3) in vec3 inBitangent;
layout(location = 4) in vec2 inUV;
layout(location = 5) in vec3 inColor;


void main() {

	mat4 MVP = ubo.viewProj * ubodyn.modelMat;
	gl_Position = MVP * vec4(inPosition, 1.0f);

    fragColor = ubo.position.xyz;
	outUV = inPosition.xy;
}