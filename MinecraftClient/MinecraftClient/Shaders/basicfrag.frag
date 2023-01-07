#version 460 core

layout (location=0) in vec2 uvs;

layout (location=1) in vec3 texPos;

layout (location=0) out vec4 out_FragColor;

layout (binding = 0) uniform sampler2D texture0;

layout (binding = 1) uniform samplerCube texture1;

void main()
{
		//out_FragColor = vec4(uvs.x,1.0f,1.0f,1.0f);
		


		out_FragColor = texture(texture0,uvs);
};
