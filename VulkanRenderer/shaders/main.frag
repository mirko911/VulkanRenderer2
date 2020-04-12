#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 inUV;

struct Material{
    vec4 abientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 strength; //x = ambient, y = specular
    int textureID;
    int normalMapID;
};

layout(set = 0, binding = 1) uniform MaterialUBO{
    Material material[10];
} materials;


layout(set = 0 ,binding = 0) uniform sampler2D texSampler[];

layout(location = 0) out vec4 outColor;

void main() {


    float specStrenght = materials.material[0].strength.y;
    float ambientStrength = materials.material[0].strength.x;

    if(int(specStrenght) == 2){
        outColor = vec4(1,1,0,1);
    }

   // outColor = vec4(fragColor, 1.0);
  //  outColor = vec4(inUV, 0, 1);
   // outColor = materials.material[0].specularColor;
   
   //int textureID = materials.material[0].normalMapID;

  //  outColor = vec4(texture(texSampler[textureID], inUV).xyz, 1);

}