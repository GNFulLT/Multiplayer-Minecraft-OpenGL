#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct VertexType
{
	float pos[3];
	float tex[2];

	VertexType()
	{
		pos[0] = 0, pos[1] = 0, pos[2] = 0, tex[0] = 0, tex[1] = 0;
	}
	VertexType(const glm::vec3& _pos, const glm::vec2& _texPos)
	{
		pos[0] = _pos[0], pos[1] = _pos[1], pos[2] = _pos[2], tex[0] = _texPos[0], tex[1] = _texPos[1];
	}
	VertexType(float x, float y, float z, float tx, float ty)
	{
		pos[0] = x, pos[1] = y, pos[2] = z, tex[0] = tx, tex[1] = ty;
	}
};