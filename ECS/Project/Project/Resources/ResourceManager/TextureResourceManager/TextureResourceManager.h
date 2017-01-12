#pragma once

#include <map>
#include <memory>

#include "../ResourceManager.h"
#include "../TextureGeneratorSelector/TextureGeneratorSelector.h"

class TextureData;

class TextureResourceManager : public ResourceManager
{

public:

	//	Default TextureResourceManager Constructor.
	TextureResourceManager(std::shared_ptr<EventQueue> newEventQueue);

	//	Default TextureResourceManager Destructor.
	~TextureResourceManager();

	//	Resource Management Functions.
	virtual void processResource(const ResourceDescription & newResourceDescription);

	//	Add a New Texture Data, under the provided Texture Name.
	virtual void addTexture(std::string newTextureName, std::shared_ptr<TextureData> newTextureData);

	//	Update the provided Texture, specified by name and the New Texture Data.
	virtual void updateTexture(std::string currentTextureName, std::shared_ptr<TextureData> newTextureData);

	//	Return a pointer to the Texture Data.
	virtual std::shared_ptr<TextureData> getTexture(std::string currentTextureName);

	//	Return a pointer to the const Texture Data.
	virtual std::shared_ptr<const TextureData> viewTexture(std::string currentTextureName);

	//	Delete the texture specified by name.
	virtual void deleteTexture(std::string deadTextureName);


private:

	//	Map the Name to the Texture Data.
	std::map<std::string, std::shared_ptr<TextureData>> mapNameToTextureData;

	//	Texture Generator Selector
	std::shared_ptr<TextureGeneratorSelector> textureGeneratorSelector;

};

