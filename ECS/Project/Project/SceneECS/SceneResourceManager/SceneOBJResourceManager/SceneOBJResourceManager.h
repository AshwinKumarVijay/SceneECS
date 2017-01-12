#pragma once
#include <memory>
#include <cerrno>
#include <iostream>
#include <string>

#include "glm\glm.hpp"


#include "../SceneResourceRequest/SceneResourceRequest.h"
#include "../../../Events/ResourceEvent/ResourceEvent.h"
#include "../../../RDFP/ResourceDescription.h"


#include "../../../Vertex/Vertex.h"

class SceneResourceManager;
class SceneGeometryResourceManager;
class SceneMaterialResourceManager;
class SceneTextureResourceManager;

class SceneOBJResource;
class GeometryData;
class MaterialData;

struct SceneOBJResourceRequest
{

};


class SceneOBJResourceManager
{

public:

	//	Default SceneOBJResouceManager Constructor.
	SceneOBJResourceManager(std::shared_ptr<SceneResourceManager> newSceneResouceManager, std::shared_ptr<SceneGeometryResourceManager> newSceneGeometryResourceManager, std::shared_ptr<SceneMaterialResourceManager> newSceneMaterialResourceManager, std::shared_ptr<SceneTextureResourceManager> newSceneTextureResourceManager);
	
	//	Default SceneOBJResouceManager Destructor.
	virtual ~SceneOBJResourceManager();

	//	Load the Resource Requested.
	virtual void loadResource(const ResourceDescription & newResourceDescription);

	//	Load the Resource Requested.
	virtual void processRequest(std::shared_ptr<SceneResourceRequest> newResourceRequest);

	//	Load the Geometry from the Obj File.
	void loadObj(const std::string & objDirectory, const std::string & sourceFilename, const std::string & baseModelName, std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & newGeometryList);
	void loadObj(const std::string & objDirectory, const std::string & sourceFilename, const std::string & baseModelName, std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> & newGeometryList, std::vector<std::pair<std::string, std::shared_ptr<MaterialData>>> & newMaterialsList);



private:

	//	Associated Scene Resource Manager.
	std::weak_ptr<SceneResourceManager> sceneResourceManager;

	//	Scene Geometry Resource Manager.
	std::shared_ptr<SceneGeometryResourceManager> sceneGeometryResourceManager;

	//	Scene Material Resource Manager.
	std::shared_ptr<SceneMaterialResourceManager> sceneMaterialResourceManager;

	//	Scene Texture Resource Manager.
	std::shared_ptr<SceneTextureResourceManager> sceneTextureResourceManager;

};

