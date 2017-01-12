#pragma once
#include <string>
#include <memory>
#include <map>

#include "../SceneResourceRequest/SceneResourceRequest.h"
#include "../../../Events/ResourceEvent/ResourceEvent.h"
#include "../../../RDFP/ResourceDescription.h"

class SceneResourceMetaData;
class SceneMaterialResource;
class SceneResourceManager;

class MaterialData;

struct SceneMaterialResourceRequest : public SceneResourceRequest
{
	std::string materialSourceType;
};


class SceneMaterialResourceManager
{

public:

	//	Default SceneMaterialResouceManager Constructor.
	SceneMaterialResourceManager(std::shared_ptr<SceneResourceManager> newSceneResourceManager);

	//	Default SceneMaterialResouceManager Destructor.
	virtual ~SceneMaterialResourceManager();

	//	Load the Resource Requested.
	virtual void loadResource(const ResourceDescription & newResourceDescription);

	//	Load the Resource Requested.
	virtual void processRequest(std::shared_ptr<SceneResourceRequest> newResourceRequest);

	//	Add a Material to the MaterialResourceManager.
	virtual void addMaterial(std::string newMaterialName, std::shared_ptr<MaterialData> newMaterialData);

	//	Update Material in the MaterialResourceManager.
	virtual void updateMaterial(std::string currentMaterialName, std::shared_ptr<MaterialData> newMaterialData);

	//	Return a Material in the MaterialResourceManager.
	virtual std::shared_ptr<MaterialData> getMaterial(std::string currentMaterialName);

	//	Return a const Material in the MaterialResourceManager.
	virtual std::shared_ptr<const MaterialData> viewMaterial(std::string currentMaterialName) const;

	//	Delete a Material in the MaterialResourceManager.
	virtual void deleteMaterial(std::string deadMaterialName);

private:

	//	Associated Scene Resouce Manager.
	std::weak_ptr<SceneResourceManager> sceneResourceManager;

	//
	std::map<std::string, std::shared_ptr<MaterialData>> mapNameToMaterialData;
};

