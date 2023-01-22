#pragma once

#include "VirtualKeyCodes.h"

namespace GNF::Common::Keyboard
{
	class IKeyboard
	{
		public:
			virtual ~IKeyboard() = default;

			virtual bool IsKeyPressed(KEY_CODE code) = 0;
	};
}