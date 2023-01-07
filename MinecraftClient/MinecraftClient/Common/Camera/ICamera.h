#pragma once

#include <glm/glm.hpp>

namespace GNF::Common::Camera
{
	class ICamera
	{
		public:
			virtual ~ICamera() = default;
			virtual glm::mat4 GetViewMatrix() = 0;
			virtual glm::vec3 GetPosition() = 0;
			virtual void Update(const float frameTime) = 0;
			virtual void InitResources() = 0;
			virtual  glm::mat4 GetViewProjMatrix() = 0;
			virtual  glm::mat4 GetWorldViewProjMatrix(const glm::mat4& world) = 0;
		private:
	};
}