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

vec2 positions[3] = vec2[](
    vec2(0.0, -0.5),
    vec2(0.5, 0.5),
    vec2(-0.5, 0.5)
);

vec3 colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

void main() {
    //gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
	 gl_Position = vec4(inPosition.xy, 0.0, 1.0);

    fragColor = ubo.position.xyz;
	outUV = inUV;
}