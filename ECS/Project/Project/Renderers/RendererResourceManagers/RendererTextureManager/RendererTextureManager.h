#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <iostream>

#include "GL\glew.h"

#include "../StringModifiers/StringModifiers.h"

class TextureData;
class TextureBufferData;

struct RendererTextureData
{
	//	Texture ID.
	GLuint textureID;

	//	Texture Type.
	GLenum textureType;

	//	Texture Width
	int textureWidth;

	//	Texture Height
	int textureHeight;
};

class RendererTextureManager
{
public:

	//	Default RendererTextureManager Constructor.
	RendererTextureManager();

	//	Default RendererTextureManager Destructor.
	virtual ~RendererTextureManager();

	//	Add a Texture to the RendererTextureManager.
	virtual void addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData);

	//	Update the Texture.
	virtual void updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData);

	//	View the Texture.
	virtual std::shared_ptr<const RendererTextureData> viewTexture(std::string currentTextureData) const;

	//	Delete the Texture.
	virtual void deleteTexture(std::string deadTextureName);


private:

	//	Map the Name to the RendererTextureData.
	std::map<std::string, std::shared_ptr<RendererTextureData>> mapNameToTextureData;

};

