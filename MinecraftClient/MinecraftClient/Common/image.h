#pragma once

#include <string>
#include "Utils/Bitmap.h"
#include "Common/glad_wrapper.h"

enum TextureType
{
	TEXTURE_2D
};


void loadImage(const char * path, GNF::Common::Bitmap** bitmap);
void loadImage(const char* path, GNF::Common::Bitmap** bitmap, bool enableVertical);

GLuint createTextureFromBitmap(const GNF::Common::Bitmap& bitmap, TextureType type);