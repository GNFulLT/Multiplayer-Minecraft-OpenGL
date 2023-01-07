#pragma once

#include "Bitmap.h"

using namespace GNF::Common;

Bitmap convertEquirectangularMapToVerticalCross(const Bitmap& b);
Bitmap convertVerticalCrossToCubeMapFaces(const Bitmap& b);
