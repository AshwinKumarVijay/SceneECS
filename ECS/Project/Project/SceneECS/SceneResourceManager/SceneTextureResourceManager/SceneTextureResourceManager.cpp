#include "SceneTextureResourceManager.h"
#include "../SceneResourceManager.h"
#include "../../../TextureGeneratorSelector/TextureGeneratorSelector.h"
#include "../../../Resources/ResourceData/TextureData/TextureData.h"
#include "../../../Resources/ResourceData/TextureData/TextureBufferData/TextureBufferData.h"

//	Default SceneTextureResourceManager Constructor.
SceneTextureResourceManager::SceneTextureResourceManager(std::shared_ptr<SceneResourceManager> newSceneResourceManager)
{
	sceneResourceManager = newSceneResourceManager;

	textureGeneratorSelector = std::make_shared<TextureGeneratorSelector>();
}

//	Default SceneTextureResourceManager Destructor
SceneTextureResourceManager::~SceneTextureResourceManager()
{

}

//	Process the Scene Resource Request.
void SceneTextureResourceManager::processRequest(std::shared_ptr<SceneResourceRequest> newResourceRequest)
{


}

void SceneTextureResourceManager::loadResource(const ResourceDescription & newResourceDescription)
{
	std::string resourceName = "None";
	std::string resourceType = "None";

	//	Get the Resource Name.
	newResourceDescription.findProperty("Resource Name", resourceName);

	//	Create the new Texture Data
	std::shared_ptr<TextureData> newTextureData = std::make_shared<TextureData>(GL_TEXTURE_2D);

	//	The Texture Source.
	std::string textureSource = "None";
	
	if (newResourceDescription.findProperty("Texture Source", textureSource))
	{
		//	The Texture Parameters.
		std::string textureParameters = "";

		//	
		std::shared_ptr<TextureBufferData> newTextureBufferData = NULL;
		newTextureBufferData = textureGeneratorSelector->generateTexture("FILE", textureSource, textureParameters);
		
		//
		newTextureData->addTextureBufferData(0, newTextureBufferData);

		//	Add the Texture to the Texture.
		addTexture(resourceName, newTextureData);
	}
}


//	Add the Texture.
void SceneTextureResourceManager::addTexture(std::string newTextureName, std::shared_ptr<TextureData> newTextureData)
{
	//	Find the Texture.
	auto textureIterator = mapNameToSceneTextureResources.find(newTextureName);

	if (textureIterator != mapNameToSceneTextureResources.end())
	{
		//	TO DO
		//	Throw Texture already present error.
	}
	else
	{
		//	Insert the Texture Data, under the appropriate name.
		mapNameToSceneTextureResources.insert(std::make_pair(newTextureName, newTextureData));

		//	Create the new Texture Resource.
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::TEXTURE_RESOURCE, ResourceEventType::RESOURCE_ADDED, "TEXTURE_MANAGER", newTextureName, newTextureData);

		//	Dispatch the creation to the EventQueue.
		sceneResourceManager.lock()->dispatchEventToEventQueue(newEvent);
	}
}

//	Update the provided Texture, specified by name and the New Texture Data.
void SceneTextureResourceManager::updateTexture(std::string currentTextureName, std::shared_ptr<TextureData> newTextureData)
{


}

//	Return a pointer to the Texture Data.
std::shared_ptr<TextureData> SceneTextureResourceManager::getTexture(const std::string & currentTextureName)
{
	auto texturei = mapNameToSceneTextureResources.find(currentTextureName);

	if (texturei != mapNameToSceneTextureResources.end())
	{
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::TEXTURE_RESOURCE, ResourceEventType::RESOURCE_UPDATED, "TEXTURE_MANAGER", currentTextureName, nullptr);
		sceneResourceManager.lock()->dispatchEventToEventQueue(newEvent);
		return texturei->second;
	}
	else
	{
		//	Throw did not find Texture Data error.
		throw "Error! Scene Texture Resource Manager : Get Texture - Texture with the specified Name Does Not Exist!";
	}
}

//	Return a pointer to the const Texture Data.
std::shared_ptr<const TextureData> SceneTextureResourceManager::viewTexture(const std::string & currentTextureName)
{
	auto texturei = mapNameToSceneTextureResources.find(currentTextureName);

	if (texturei != mapNameToSceneTextureResources.end())
	{
		return texturei->second;
	}
	else
	{
		//	Throw did not find Texture Data error.
		throw "Error! Scene Texture Resource Manager : View Texture - Texture with the specified Name Does Not Exist!";
	}
}

//	Delete the texture specified by name.
void SceneTextureResourceManager::deleteTexture(const std::string & deadTextureName)
{
	auto texturei = mapNameToSceneTextureResources.find(deadTextureName);

	if (texturei != mapNameToSceneTextureResources.end())
	{
		mapNameToSceneTextureResources.erase(deadTextureName);
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::TEXTURE_RESOURCE, ResourceEventType::RESOURCE_DESTROYED, "TEXTURE_MANAGER", deadTextureName, nullptr);
		sceneResourceManager.lock()->dispatchEventToEventQueue(newEvent);
	}
	else
	{
		//	Throw did not find Texture Data error.
		throw "Error! Scene Texture Resource Manager : Delete Texture - Texture with the specified Name Does Not Exist!";
	}

}

