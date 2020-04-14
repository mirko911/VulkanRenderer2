#version 460
#extension GL_ARB_separate_shader_objects : enable

struct Camera {
	mat4 projection;
	mat4 view;
    mat4 viewProj;
    vec4 position;
};

layout(set = 0, binding = 2) uniform UBO{
	Camera cameras[16];
} ubo;

layout(set = 0, binding = 3) uniform UBODyn{
	mat4 modelMat;
	int materialID;
	int cameraID;
} ubodyn;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inTangent;
layout(location = 3) in vec3 inBitangent;
layout(location = 4) in vec2 inUV;
layout(location = 5) in vec3 inColor;


void main() {
	Camera camera = ubo.cameras[ubodyn.cameraID];

	mat4 MVP = camera.viewProj * ubodyn.modelMat;
	gl_Position = MVP * vec4(inPosition, 1.0f);
}