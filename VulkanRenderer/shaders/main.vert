#version 460
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec3 fragColor;

layout(set = 0, binding = 0) uniform UBO{
	mat4 test;
	vec4 test2;
} ubo;


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
	

    fragColor = colors[gl_VertexIndex];
	
	if(ubo.test2.x != 0){
		fragColor = ubo.test2.xyz;
	}
}