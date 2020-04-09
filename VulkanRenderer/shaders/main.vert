#version 460
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec3 fragColor;

layout(set = 0, binding = 0) uniform UBO{
	mat4 projection;
	mat4 view;
    mat4 viewProj;
    vec4 position;
} ubo;

layout(set = 0, binding = 1) uniform UBODyn{
	mat4 modelMat;
} ubodyn;

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
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
	

    fragColor = ubo.position.xyz;
	
}