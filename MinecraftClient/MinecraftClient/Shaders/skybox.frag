#version 460 core

layout (location=0) in vec3 dir;

layout (location=0) out vec4 out_FragColor;

layout (binding=1) uniform samplerCube texture1;

void main()
{
	//out_FragColor = vec4(0,0,1.0f,1.0f);
	out_FragColor = texture(texture1, dir);
};