#include "TextureBufferData.h"


//	Default TextureBufferData Constructor.
TextureBufferData::TextureBufferData()
{
	textureWidth = 0;
	textureHeight = 0;
	pixelData = NULL;
}

//	Default TextureBufferData Destructor.
TextureBufferData::~TextureBufferData()
{
	cleanTextureBufferData();
}

//	Initialize the Texture Buffer Data
void TextureBufferData::initializeTextureBufferData(ILubyte * newData, const int & newWidth, const int & newHeight, const GLuint & newImageInternalFormat, const GLuint & newImageFormat)
{
	cleanTextureBufferData();

	textureWidth = newWidth;
	textureHeight = newHeight;
	imageInternalFormat = newImageInternalFormat;
	imageFormat = newImageFormat;

	pixelData = new GLubyte[newWidth * newHeight * 4];

	//	Iterate and copy the pixels from the image.
	for (int i = 0; i < textureHeight; i++)
	{
		for (int j = 0; j < textureWidth; j++)
		{
			pixelData[((i * textureWidth + j) * 4) + 0] = newData[((i * textureWidth + j) * 4) + 0];
			
			pixelData[((i * textureWidth + j) * 4) + 1] = newData[((i * textureWidth + j) * 4) + 1];

			pixelData[((i * textureWidth + j) * 4) + 2] = newData[((i * textureWidth + j) * 4) + 2];
			
			pixelData[((i * textureWidth + j) * 4) + 3] = newData[((i * textureWidth + j) * 4) + 3];
		}
	}
}

//	Initialize the Texture Buffer Data.
void TextureBufferData::initializeTextureBufferData(void * newData, const int & newWidth, const int & newHeight, const GLuint & newImageInternalFormat, const GLuint & newImageFormat)
{
	cleanTextureBufferData();

	textureWidth = newWidth;
	textureHeight = newHeight;
	imageInternalFormat = newImageInternalFormat;
	imageFormat = newImageFormat;

	pixelData = new GLubyte[newWidth * newHeight * 4];

	//	Iterate and copy the pixels from the image.
	for (int i = 0; i < textureHeight; i++)
	{
		for (int j = 0; j < textureWidth; j++)
		{
			pixelData[((i * textureWidth + j) * 4) + 0] = ((GLubyte *)newData)[((i * textureWidth + j) * 4) + 0];

			pixelData[((i * textureWidth + j) * 4) + 1] = ((GLubyte *)newData)[((i * textureWidth + j) * 4) + 1];

			pixelData[((i * textureWidth + j) * 4) + 2] = ((GLubyte *)newData)[((i * textureWidth + j) * 4) + 2];

			pixelData[((i * textureWidth + j) * 4) + 3] = ((GLubyte *)newData)[((i * textureWidth + j) * 4) + 3];
		}
	}

}

//	View the Texture Buffer Data.
GLubyte const * TextureBufferData::viewTextureBufferData() const
{
	return pixelData;
}


//	Return the width of the texture.
int TextureBufferData::getWidth() const
{
	return textureWidth;
}

//	Return the height of the texture.
int TextureBufferData::getHeight() const
{
	return textureHeight;
}

//	Return the Internal Image Format.
GLuint TextureBufferData::getImageInternalFormat() const
{
	return imageInternalFormat;
}

//	Return the Image Format.
GLuint TextureBufferData::getImageFormat() const
{
	return imageFormat;
}

//	Clean the Texture Data.
void TextureBufferData::cleanTextureBufferData()
{
	//	Pixel Data.
	if (pixelData != NULL)
	{
		delete pixelData;
		pixelData = NULL;
	}

	//	Texture Width.
	textureWidth = 0;
	
	//	Texture Height.
	textureHeight = 0;

}
