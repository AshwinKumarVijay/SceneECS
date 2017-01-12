#include "TextureResourceManager.h"
#include "../../ResourceData/TextureData/TextureData.h"	
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"

//	Default TextureResourceManager Constructor
TextureResourceManager::TextureResourceManager(std::shared_ptr<EventQueue> newEventQueue)
	: ResourceManager(newEventQueue, "TEXTURE_MANAGER")
{
	textureGeneratorSelector = std::make_shared<TextureGeneratorSelector>();
}

//	Default TextureResourceManager Destructor
TextureResourceManager::~TextureResourceManager()
{

}

//	Process the provided resource.
void TextureResourceManager::processResource(const ResourceDescription & newResourceDescription)
{
	std::string resourceName = "None";
	std::string resourceType = "None";

	//	
	if (newResourceDescription.findProperty("Resource Type", resourceType))
	{
		if (resourceType == "Texture")
		{
			//	Get the Resource Name.
			newResourceDescription.findProperty("Resource Name", resourceName);

			//	Get the Texture Type.
			std::string textureType = "Texture 2D";
			newResourceDescription.findProperty("Texture Cube Map", textureType);

			//	Get the Texture Generation.
			std::string textureGeneration = "None";
			newResourceDescription.findProperty("Texture Generation", textureGeneration);

			//	Get the Texture Parameters.
			std::string textureParameters = "None";
			newResourceDescription.findProperty("Texture Parameters", textureParameters);

			//	Check the Texture Type
			std::shared_ptr<TextureData> newTextureData = NULL;

			//	
			if (textureType == "Texture 2D")
				newTextureData = std::make_shared<TextureData>(GL_TEXTURE_2D);

			//
			if (textureType == "Texture Cube Map")
				newTextureData = std::make_shared<TextureData>(GL_TEXTURE_CUBE_MAP);

			//	
			std::string textureSource0 = "None";
			newResourceDescription.findProperty("Texture Source 0", textureSource0);

			std::string textureSource1 = "None";
			newResourceDescription.findProperty("Texture Source 1", textureSource1);

			std::string textureSource2 = "None";
			newResourceDescription.findProperty("Texture Source 2", textureSource2);

			std::string textureSource3 = "None";
			newResourceDescription.findProperty("Texture Source 3", textureSource3);

			std::string textureSource4 = "None";
			newResourceDescription.findProperty("Texture Source 4", textureSource4);

			std::string textureSource5 = "None";
			newResourceDescription.findProperty("Texture Source 5", textureSource5);


			//	
			std::shared_ptr<TextureBufferData> newTextureBufferData = NULL;

			newTextureBufferData = textureGeneratorSelector->generateTexture(textureGeneration, textureSource0, textureParameters);
			newTextureData->addTextureBufferData(0, newTextureBufferData);

			newTextureBufferData = textureGeneratorSelector->generateTexture(textureGeneration, textureSource1, textureParameters);
			newTextureData->addTextureBufferData(1, newTextureBufferData);

			newTextureBufferData = textureGeneratorSelector->generateTexture(textureGeneration, textureSource2, textureParameters);
			newTextureData->addTextureBufferData(2, newTextureBufferData);

			newTextureBufferData = textureGeneratorSelector->generateTexture(textureGeneration, textureSource3, textureParameters);
			newTextureData->addTextureBufferData(3, newTextureBufferData);

			newTextureBufferData = textureGeneratorSelector->generateTexture(textureGeneration, textureSource4, textureParameters);
			newTextureData->addTextureBufferData(4, newTextureBufferData);

			newTextureBufferData = textureGeneratorSelector->generateTexture(textureGeneration, textureSource5, textureParameters);
			newTextureData->addTextureBufferData(5, newTextureBufferData);

			//	
			addTexture(resourceName, newTextureData);
		}
	}
}

//	Add a Texture, specified by name.
void TextureResourceManager::addTexture(std::string newTextureName, std::shared_ptr<TextureData> newTextureData)
{
	//	Find the Texture.
	auto textureIterator = mapNameToTextureData.find(newTextureName);

	if (textureIterator != mapNameToTextureData.end())
	{
		//	TO DO
		//	Throw Geometry already present error.
	}
	else
	{
		//	Insert the Texture Data, under the appropriate name.
		mapNameToTextureData.insert(std::make_pair(newTextureName, newTextureData));

		//	Create the new Texture Resource.
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::TEXTURE_RESOURCE, ResourceEventType::RESOURCE_ADDED, "TEXTURE_MANAGER", newTextureName, newTextureData);

		//	Dispatch the creation to the EventQueue.
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
}

//	Update the Texture, specified by name.
void TextureResourceManager::updateTexture(std::string currentTextureName, std::shared_ptr<TextureData> newTextureData)
{
	//	Find the Texture.
	auto textureIterator = mapNameToTextureData.find(currentTextureName);

	if (textureIterator != mapNameToTextureData.end())
	{
		//	Set the new Texture Data associated with the Texture.
		textureIterator->second = newTextureData;

		//	Create the update the Texture Resource.
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::TEXTURE_RESOURCE, ResourceEventType::RESOURCE_UPDATED, "TEXTURE_MANAGER", currentTextureName, newTextureData);
		
		//	Dispatch the creation to the EventQueue.
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find TextureData error.
	}
}

//	Return the Texture, specified by name.
std::shared_ptr<TextureData> TextureResourceManager::getTexture(std::string currentTextureName)
{
	//	Find the Texture.
	auto textureIterator = mapNameToTextureData.find(currentTextureName);

	//	
	if (textureIterator != mapNameToTextureData.end())
	{
		//	Return the associated the TextureData.
		return textureIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find TextureData error.
		return NULL;
	}
}

//	Return the Texture, specified by name. Return a const pointer.
std::shared_ptr<const TextureData> TextureResourceManager::viewTexture(std::string currentTextureName)
{
	//	Find the Texture.
	auto textureIterator = mapNameToTextureData.find(currentTextureName);

	if (textureIterator != mapNameToTextureData.end())
	{
		//	Return the associated the TextureData.
		return textureIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find TextureData error.
		return NULL;
	}
}

//	Delete the Texture, specified by name.
void TextureResourceManager::deleteTexture(std::string deadTextureName)
{
	//	Find the Texture.
	auto textureIterator = mapNameToTextureData.find(deadTextureName);

	if (textureIterator != mapNameToTextureData.end())
	{
		//	
		mapNameToTextureData.erase(deadTextureName);

		//	Create the delete Texture event.
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::TEXTURE_RESOURCE, ResourceEventType::RESOURCE_DESTROYED, "TEXTURE_MANAGER", deadTextureName, nullptr);

		//	Dispatch the event to the EventQueue.
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find TextureData error.
	}
}
