#pragma once

#include <stdint.h>

namespace GNF::Primitive
{
	enum Direction : uint8_t
	{
		Up = 0,
		Right,
		Down,
		Left,
		Front,
		Back
	};
}