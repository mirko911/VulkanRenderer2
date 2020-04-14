#version 460
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec2 outUV;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out vec3 outLightVec;
layout(location = 3) out vec3 outViewVec;
layout(location = 4) out int outMaterialID;

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

	vec4 pos = (camera.view * ubodyn.modelMat * vec4(inPosition,1.0f));

	vec3 lPos =  mat3(camera.view) * vec3(50,50,50);

	outLightVec = lPos - pos.xyz;
	outViewVec = -pos.xyz;
	outUV = inUV;
	outNormal = mat3(camera.view) * mat3(transpose(inverse(ubodyn.modelMat))) * inNormal;
	outMaterialID = ubodyn.materialID;
}