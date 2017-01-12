#pragma once
#include <map>
#include <memory>

#include "../../ECS/MainResourceManager/MainResourceManager.h"

#include "SceneGeometryResourceManager\SceneGeometryResourceManager.h"
#include "SceneMaterialResourceManager\SceneMaterialResourceManager.h"
#include "SceneTextureResourceManager\SceneTextureResourceManager.h"

#include "SceneOBJResourceManager\SceneOBJResourceManager.h"

#include "SceneResourceRequest/SceneResourceRequest.h"

#include "../RDFP/RDFP.h"

class ECSEvent;
	
class SceneResourceManager : public MainResourceManager
{

public:

	//	Default SceneResourceManager Constructor.
	SceneResourceManager();

	//	Default SceneResourceManager Destructor.
	virtual ~SceneResourceManager();

	//	TEMPORARAY HACKY REMOVE LATER
	virtual void initializeResourceManagers();

	//	Load the Resources From a given file.
	virtual void loadResourcesFromFile(const std::string & resourceFile);

	virtual void loadResource(const ResourceDescription & currentResourceDescription);

	//	Load the Resource Requested.
	virtual void processResource(std::shared_ptr<SceneResourceRequest> newResourceRequest);

	//	Dispatch the Resource Event.
	virtual void dispatchEventToEventQueue(std::shared_ptr<ECSEvent> newEvent);

private:

	//	Scene Geometry Resource Manager.
	std::shared_ptr<SceneGeometryResourceManager> sceneGeometryResourceManager;

	//	Scene Material Resource Manager.
	std::shared_ptr<SceneMaterialResourceManager> sceneMaterialResourceManager;

	//	Scene Texture Resource Manager.
	std::shared_ptr<SceneTextureResourceManager> sceneTextureResourceManager;

	//	Scene OBJ Resource Manager.
	std::shared_ptr<SceneOBJResourceManager> sceneOBJResourceManager;

	//	The Resources and the Resource Description.
	std::map<std::string, ResourceDescription> resources;

	//	Resource Description File Parser.
	RDFP rdfp;
};

