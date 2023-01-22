#pragma once

#include "IWindow.h"

namespace GNF::Common::Windowing
{
	class Window : public IWindow
	{
	public:
		virtual ~Window() = default;
		virtual bool IsOpen() override;
		virtual const glm::ivec2& GetSize() override;

	};
}
