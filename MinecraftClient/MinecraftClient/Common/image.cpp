#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


//! Helper Funcs
//# -----------------------------------------------------

inline GLuint createTexture2DFromBitmap(const GNF::Common::Bitmap& bitmap)
{
	GLuint texture;
	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	glTextureParameteri(texture, GL_TEXTURE_MAX_LEVEL, 0);
	glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureStorage2D(texture, 1, GL_RGB32F, bitmap.w_, bitmap.h_);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTextureSubImage2D(texture, 0, 0, 0, bitmap.w_, bitmap.h_, GL_RGB, GL_FLOAT, bitmap.data_.data());

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

//# -----------------------------------------------------

void loadImage(const char* path, GNF::Common::Bitmap** bitmap)
{
	stbi_set_flip_vertically_on_load(true);

	int w, h, comp;
	const float* img = stbi_loadf(path, &w, &h, &comp, 3);

	GNF::Common::Bitmap* bit = new GNF::Common::Bitmap(w, h, comp, GNF::Common::eBitmapFormat_Float, img);

	(*bitmap) = bit;


	stbi_image_free((void*)img);

	
}
void loadImage(const char* path, GNF::Common::Bitmap** bitmap,bool verticalEnabled)
{
	stbi_set_flip_vertically_on_load(verticalEnabled);

	int w, h, comp;
	const float* img = stbi_loadf(path, &w, &h, &comp, 3);

	GNF::Common::Bitmap* bit = new GNF::Common::Bitmap(w, h, comp, GNF::Common::eBitmapFormat_Float, img);

	(*bitmap) = bit;


	stbi_image_free((void*)img);

}

GLuint createTextureFromBitmap(const GNF::Common::Bitmap& bitmap, TextureType type)
{
	switch ( type)
	{
		case TEXTURE_2D:
			return createTexture2DFromBitmap(bitmap);
		default:
			return 0;
	}
}


