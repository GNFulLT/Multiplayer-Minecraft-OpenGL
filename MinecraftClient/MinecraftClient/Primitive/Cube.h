#pragma once

#include "Mesh.h"

namespace GNF::Primitive
{
	class Cube : public Mesh
	{
		public:
			Cube(float width, float height,const glm::vec3& worldPos);
			Cube(glm::vec3& worldPos);
			Cube(Cube&) = delete;
			Cube& operator = (Cube&) = delete;
		private:
	};
}