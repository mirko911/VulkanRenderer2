#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable

layout(location = 0) in vec2 inUV;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inLightVec;
layout(location = 3) in vec3 inViewVec;
layout(location = 4) flat in int inMaterialID;

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


Material getMaterial(int ID){
    return materials.material[ID];
}


layout(set = 0 ,binding = 0) uniform sampler2D texSampler[];

layout(location = 0) out vec4 outColor;

const vec3 lightPos = vec3(50,50,50);

void main() {
    const Material material = getMaterial(inMaterialID);


    vec3 N = normalize(inNormal);
//	if(ubodyn.normalMapID >= 0){
//		vec3 normalMapPart = texture(texSampler[int(ubodyn.normalMapID)], inUV).xyz;
//		N = normalize(N + (normalMapPart * 2.0 - 1.0));
//	}

	vec3 ambient = material.strength.x * material.abientColor.xyz;
	vec3 L = normalize(inLightVec);
	vec3 V = normalize(inViewVec);
	vec3 R = reflect(-L, N);
//
	float diff = max(dot(N, L), 0.0);
	vec3 diffuse = diff * material.diffuseColor.xyz;
//
	float spec = pow(max(dot(R, V), 0.0), 32);
	vec3 specular = material.strength.y *material.specularColor.xyz * spec;
//

    if(material.textureID >= 0){
    	outColor = texture(texSampler[material.textureID], inUV) * vec4(ambient + specular, 1.0f) ;
    }else{
        outColor =  vec4(ambient + diffuse + specular, 1.0f) ;
    }

   // float specStrenght = materials.material[0].strength.y;
  //  float ambientStrength = materials.material[0].strength.x;

  //  if(int(specStrenght) == 2){
  //      outColor = vec4(1,1,0,1);
 //   }

   // outColor = vec4(fragColor, 1.0);
  //  outColor = vec4(inUV, 0, 1);
   // outColor = materials.material[0].specularColor;
   
   //int textureID = materials.material[0].normalMapID;

  //  outColor = vec4(texture(texSampler[textureID], inUV).xyz, 1);

}