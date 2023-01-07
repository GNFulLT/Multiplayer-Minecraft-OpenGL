#version 460 core

/*
layout(std140, binding = 0) uniform PerFrameData
{
	uniform mat4 MVP;
};

struct Vertex
{
	float p[3];
	float tc[2];
};

layout(std430, binding = 1) restrict readonly buffer Vertices
{
	Vertex in_Vertices[];
};

vec3 getPosition(int i)
{
	return vec3(in_Vertices[i].p[0], in_Vertices[i].p[1], in_Vertices[i].p[2]);
}

vec2 getTexCoord(int i)
{
	return vec2(in_Vertices[i].tc[0], in_Vertices[i].tc[1]);
}

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
*/


layout(std140, binding = 0) uniform PerFrameData
{
	uniform mat4 model;
	uniform mat4 MVP;
	uniform vec4 cameraPos;
};

struct Vertex
{
	float pos[3];
	float tex[2];
};

layout(std430, binding = 1) restrict readonly buffer Vertices
{
	Vertex in_Vertices[];
};


vec3 getPosition(int i)
{
	return vec3(in_Vertices[i].pos[0], in_Vertices[i].pos[1], in_Vertices[i].pos[2]);
}

vec2 getTexCoord(int i)
{
	return vec2(in_Vertices[i].tex[0], in_Vertices[i].tex[1]);
}

layout (location=0) out vec2 uv;
void main()
{
	vec3 pos = getPosition(gl_VertexID);
    gl_Position = MVP * vec4(pos, 1.0); // see how we directly give a vec3 to vec4's constructor

	uv = getTexCoord(gl_VertexID);
}


/*#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
  

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
}*/