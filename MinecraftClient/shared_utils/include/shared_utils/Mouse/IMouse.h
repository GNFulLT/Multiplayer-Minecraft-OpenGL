#pragma once

#include <glm/glm.hpp>

#define	SUPPORTED_MOUSE_KEY_NUM 3

namespace GNF::SU::Mouse
{
	
	enum MOUSE_KEY
	{
		MOUSE_LEFT = 0,MOUSE_RIGHT,MOUSE_MIDDLE
	};
	class IMouse
	{
	public:
		virtual ~IMouse() = default;

		virtual const glm::vec2 GetMousePos() = 0;
		virtual const glm::vec2 GetPrevMousePos() = 0;
		virtual bool IsMouseKeyPressing(MOUSE_KEY key) = 0;
	};
}