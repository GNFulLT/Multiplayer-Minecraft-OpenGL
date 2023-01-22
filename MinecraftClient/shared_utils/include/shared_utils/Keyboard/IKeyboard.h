#pragma once

#include "VirtualKeyCodes.h"

namespace GNF::SU::Keyboard
{
	class IKeyboard
	{
	public:
		virtual ~IKeyboard() = default;

		virtual bool IsKeyPressed(KEY_CODE code) = 0;
	};
}