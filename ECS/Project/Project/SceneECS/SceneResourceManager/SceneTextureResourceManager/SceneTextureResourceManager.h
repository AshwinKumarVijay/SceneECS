#pragma once
#include <memory>
#include <string>
#include <map>

#include "../SceneResourceRequest/SceneResourceRequest.h"
#include "../../../Resources/ResourceData/TextureData/TextureData.h"
#include "../../../Events/ResourceEvent/ResourceEvent.h"

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


private:

	//	Associated Scene Resouce Manager.
	std::weak_ptr<SceneResourceManager> sceneResourceManager;

	//
	std::map<std::string, std::shared_ptr<TextureData>> mapNameToSceneTextureResources;

};

