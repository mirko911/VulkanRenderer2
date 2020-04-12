#version 460
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 inUV;


layout(set = 0 ,binding = 0) uniform sampler2D texSampler[];

struct Material{
    vec4 abientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 strength;
    int textureID;
    int normalMapID;
};

layout(set = 0, binding = 1) uniform MaterialUBO{
    Material material[10];
} materials;

layout(location = 0) out vec4 outColor;

void main() {
   // outColor = vec4(fragColor, 1.0);
    outColor = vec4(texture(texSampler[0], inUV).xyz, 1);
    outColor = vec4(inUV, 0, 1);
}