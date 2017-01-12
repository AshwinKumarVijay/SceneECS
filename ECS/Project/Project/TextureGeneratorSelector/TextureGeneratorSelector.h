#pragma once

#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <string>

#include "GL\glew.h"

#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"

#include "SDL\SDL_ttf.h"

#include "glm\glm.hpp"
#include "../StringModifiers/StringModifiers.h"

class TextureData;
class TextureBufferData;

class TextureGeneratorSelector
{
public:

	//	Default TextureGeneratorSelector Constructor.
	TextureGeneratorSelector();

	//	Default TextureGeneratorSelector Destructor.
	virtual ~TextureGeneratorSelector();

	//	Generate the texture from the provided parameters.
	std::shared_ptr<TextureBufferData> generateTexture(std::string textureGenerationType, std::string textureFileName, std::string textureParameters);

	//	Load the Texture From File - uses DevIL.
	virtual void loadTextureFromFile(std::string textureFileName, std::shared_ptr<TextureBufferData> newTextureData);

	//	Create the Texture from Text.
	virtual std::shared_ptr<TextureBufferData> createTexturefromText(const std::string & textString, const std::string & textFont, const int & fontSize);

private:

	//	Flag to indicate whether the initialization of the DevIL library has been completed.
	static bool DevILInitializationComplete;

};

