#include "SceneResourceManager.h"



//	Default SceneResourceManager Constructor.
SceneResourceManager::SceneResourceManager()
{

}


//	Default SceneResourceManager Destructor.
SceneResourceManager::~SceneResourceManager()
{
	
}

void SceneResourceManager::initializeResourceManagers()
{
	//	Create the Geometry Resource Manager.
	sceneGeometryResourceManager = std::make_shared<SceneGeometryResourceManager>(std::dynamic_pointer_cast<SceneResourceManager>(this->shared_from_this()));

	//	Create the Material Resource Manager.
	sceneMaterialResourceManager = std::make_shared<SceneMaterialResourceManager>(std::dynamic_pointer_cast<SceneResourceManager>(this->shared_from_this()));
	
	//	Create the Texture Resource Manager.
	sceneTextureResourceManager = std::make_shared<SceneTextureResourceManager>(std::dynamic_pointer_cast<SceneResourceManager>(this->shared_from_this()));

	//	Create the Geometry Resource Manager.
	sceneOBJResourceManager = std::make_shared<SceneOBJResourceManager>(std::dynamic_pointer_cast<SceneResourceManager>(this->shared_from_this()), sceneGeometryResourceManager, sceneMaterialResourceManager, sceneTextureResourceManager);

}

//	Load the Resources From a given file.
void SceneResourceManager::loadResourcesFromFile(const std::string & resourceFile)
{
	//	Parse the Resource Description File.
	rdfp.parseResourceDescriptionFile(resourceFile, resources);

	//	Iterate over all the resources.
	for (auto resourcesItr = resources.begin(); resourcesItr != resources.end(); resourcesItr++)
	{
		loadResource(resourcesItr->second);
	}
}

//	
void SceneResourceManager::loadResource(const ResourceDescription & currentResourceDescription)
{
	//	Get the appropriate Resource Type.
	std::string resourceType = "None";
	bool hasType = currentResourceDescription.findProperty("Resource Type", resourceType);

	//	Check if we actually have the type, and can use it to appropriately process the data.
	if (hasType)
	{
		//	Material Resource.
		if (resourceType == "Material")
		{
			sceneMaterialResourceManager->loadResource(currentResourceDescription);
		}

		if (resourceType == "OBJ")
		{
			sceneOBJResourceManager->loadResource(currentResourceDescription);
		}
	}
	else
	{
		std::cout << "Error! SceneECS: Process Resource - Resource Has No Type! " << std::endl;
	}


}

//	Load the Resource Requested.
void SceneResourceManager::processResource(std::shared_ptr<SceneResourceRequest> newResourceRequest)
{
		
	//	
	if (newResourceRequest->getResourceType() == "Geometry")
	{
		sceneGeometryResourceManager->processRequest(newResourceRequest);
	}

	//	
	if (newResourceRequest->getResourceType() == "Material")
	{
		sceneMaterialResourceManager->processRequest(newResourceRequest);
	}

	//	
	if (newResourceRequest->getResourceType() == "Texture")
	{
		sceneTextureResourceManager->processRequest(newResourceRequest);
	}

	//	
	if (newResourceRequest->getResourceType() == "OBJ")
	{
		sceneOBJResourceManager->processRequest(newResourceRequest);
	}



}

//	Dispatch the Resource Event.
void SceneResourceManager::dispatchEventToEventQueue(std::shared_ptr<ECSEvent> newEvent)
{
	MainResourceManager::dispatchEventToEventQueue(newEvent);
}
