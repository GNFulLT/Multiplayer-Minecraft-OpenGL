#pragma once

#include <glm/glm.hpp>

namespace GNF::Common::Windowing
{
	class IWindow
	{
		public:
			virtual ~IWindow() = default;
			virtual bool IsOpen() = 0;
			virtual const glm::ivec2& GetSize() = 0;
			
	};
}
