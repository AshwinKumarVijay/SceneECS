#include "TextureData.h"


//	Default TextureData Constructor
TextureData::TextureData(GLenum newTextureType)
{
	textureType = newTextureType;
}


//	Default TextureData Destructor
TextureData::~TextureData()
{

}

//	Return the Texture Type.
GLenum TextureData::getTextureType() const
{
	return textureType;
}

//	Add the Texture Buffer Data.
void TextureData::addTextureBufferData(int textureIndex, std::shared_ptr<TextureBufferData> newTextureBufferData)
{
	textureBuffers[textureIndex] = newTextureBufferData;
}

//	
std::shared_ptr<const TextureBufferData> TextureData::viewTextureBufferData(int textureIndex) const
{
	return textureBuffers[textureIndex];
}

//	Return the Texture Buffer Data.
std::shared_ptr<TextureBufferData> TextureData::getTextureBufferData(int textureIndex)
{
	return textureBuffers[textureIndex];
}

//	Delete the Texture Buffer Data.
void TextureData::deleteTextureBufferData(int textureIndex)
{
	textureBuffers[textureIndex] = NULL;
}
