#include "SceneShaderResourceManager.h"


//	
SceneShaderResourceManager::SceneShaderResourceManager(std::shared_ptr<SceneResourceManager> newSceneResourceManager)
{
	sceneResourceManager = newSceneResourceManager;
}

//	
SceneShaderResourceManager::~SceneShaderResourceManager()
{

}


//	Process the Request
void SceneShaderResourceManager::processRequest(std::shared_ptr<SceneResourceRequest> newResourceRequest)
{


}
