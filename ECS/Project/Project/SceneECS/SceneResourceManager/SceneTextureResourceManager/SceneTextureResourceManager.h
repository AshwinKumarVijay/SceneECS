#pragma once
#include <memory>
#include <string>
#include <map>

#include "../SceneResourceRequest/SceneResourceRequest.h"
#include "../../../Resources/ResourceData/TextureData/TextureData.h"
#include "../../../Events/ResourceEvent/ResourceEvent.h"
#include "../../../Resources/ResourceData/ResourceData.h"

class TextureGeneratorSelector;
class TextureBufferData;
class ResourceDescription;

class SceneResourceMetaData;
class SceneTextureResource;
class SceneResourceManager;


struct SceneTextureResourceRequest : public SceneResourceRequest
{
	std::string textureSourceType;
	std::string textureName;
};


class SceneTextureResourceManager
{

public:

	//	Default SceneTextureResourceManager Constructor.
	SceneTextureResourceManager(std::shared_ptr<SceneResourceManager> newSceneResourceManager);

	//	Default SceneTextureResourceManager Destructor.
	virtual ~SceneTextureResourceManager();

	//	Load the Resource Requested.
	virtual void processRequest(std::shared_ptr<SceneResourceRequest> newResourceRequest);

	//
	virtual void loadResource(const ResourceDescription & newResourceDescription);

	//	Add a New Texture Data, under the provided Texture Name.
	virtual void addTexture(std::string newTextureName, std::shared_ptr<TextureData> newTextureData);

	//	Update the provided Texture, specified by name and the New Texture Data.
	virtual void updateTexture(std::string currentTextureName, std::shared_ptr<TextureData> newTextureData);

	//	Return a pointer to the Texture Data.
	virtual std::shared_ptr<TextureData> getTexture(const std::string & currentTextureName);

	//	Return a pointer to the const Texture Data.
	virtual std::shared_ptr<const TextureData> viewTexture(const std::string & currentTextureName);

	//	Delete the texture specified by name.
	virtual void deleteTexture(const std::string & deadTextureName);

private:

	//	Associated Scene Resouce Manager.
	std::weak_ptr<SceneResourceManager> sceneResourceManager;

	//	Texture Generator Selector.
	std::shared_ptr<TextureGeneratorSelector> textureGeneratorSelector;

	//	Map the Name to the Scene Texture Resources.
	std::map<std::string, std::shared_ptr<TextureData>> mapNameToSceneTextureResources;

};

