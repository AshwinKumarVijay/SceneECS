#pragma once
#include <map>
#include <string>
#include <memory>

#include "../SceneECS/../Resources/ResourceData/ShaderData/ShaderData.h"
#include "../SceneResourceRequest/SceneResourceRequest.h"


class SceneResourceManager;

struct SceneShaderResourceRequest : public SceneResourceRequest
{


};

class SceneShaderResourceManager
{

public:

	//	Default Scene Shader Resource Mangaer Constructor.
	SceneShaderResourceManager(std::shared_ptr<SceneResourceManager> newSceneResourceManager);

	//	Scene Shader Resouce Manager Destructor.
	virtual ~SceneShaderResourceManager();

	//	Load the Resource Requested.
	virtual void processRequest(std::shared_ptr<SceneResourceRequest> newResourceRequest);

private:

	//	Associated Scene Resouce Manager.
	std::weak_ptr<SceneResourceManager> sceneResourceManager;

	//
	std::map<std::string, std::shared_ptr<ShaderData>> mapNameToSceneTextureResources;

};

