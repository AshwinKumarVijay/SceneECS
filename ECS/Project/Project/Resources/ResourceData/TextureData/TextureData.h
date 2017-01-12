#pragma once
#include <memory>
#include <vector>

#include "GL\glew.h"

#include "glm\glm.hpp"

#include "../ResourceData.h"
#include "TextureBufferData\TextureBufferData.h"


class TextureData : public ResourceData
{

public:

	//	Default TextureData Constructor.
	TextureData(GLenum newTextureType);

	//	Default TextureData Destructor.
	virtual ~TextureData();

	//	Return the TextureType.
	GLenum getTextureType() const;

	//	Add Comments - TO DO
	void addTextureBufferData(int textureIndex, std::shared_ptr<TextureBufferData> newTextureBufferData);

	//	Add Comments - TO DO
	std::shared_ptr<const TextureBufferData> viewTextureBufferData(int textureIndex) const;

	//	Add Comments - TO DO
	std::shared_ptr<TextureBufferData> getTextureBufferData(int textureIndex);

	//	Add Comments - TO DO
	void deleteTextureBufferData(int textureIndex);


private:

	//	The Texture Type.
	GLenum textureType;

	//	The Texture Buffer Data.
	std::shared_ptr<TextureBufferData> textureBuffers[6];

};

