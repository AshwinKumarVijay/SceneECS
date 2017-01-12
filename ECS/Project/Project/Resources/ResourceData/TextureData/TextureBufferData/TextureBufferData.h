#pragma once
#include <memory>
#include <vector>


#include "GL\glew.h"

#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"

#include "SDL\SDL_ttf.h"
#include "SDL\SDL_image.h"

#include "glm\glm.hpp"


class TextureBufferData
{
public:

	//	Default TextureBufferData Constructor.
	TextureBufferData();

	//	Default TextureBufferData Destructor.
	virtual ~TextureBufferData();

	//	Initialize the Texture Buffer Data from DevIL.
	virtual void initializeTextureBufferData(ILubyte * newData, const int & newWidth, const int & newHeight, const GLuint & newImageInternalFormat, const GLuint & newImageFormat);

	//	Initialize the Texture Buffer Data from SDL.
	virtual void initializeTextureBufferData(void * newData, const int & newWidth, const int & newHeight, const GLuint & newImageInternalFormat, const GLuint & newImageFormat);

	//	View the Texture Buffer Data.
	virtual GLubyte const * viewTextureBufferData() const;

	//	Return the Width of the Texture Buffer Data.
	virtual int getWidth() const;

	//	Return the Height of the Texture Buffer Data.
	virtual int getHeight() const;

	//	Return the Internal Image Format.
	virtual GLuint getImageInternalFormat() const;

	//	The Image Format.
	virtual GLuint getImageFormat() const;

	//	Clean the Texture Buffer Data.
	virtual void cleanTextureBufferData();


private:

	//	Texture Width.
	int textureWidth;

	//	Texture Height.
	int textureHeight;
	
	//	Pixel Data.
	GLubyte * pixelData;

	//	The Internal Image Format.
	GLuint imageInternalFormat;

	//	The Image Format.
	GLuint imageFormat;


};


