#include "SceneTextureResourceManager.h"



SceneTextureResourceManager::SceneTextureResourceManager(std::shared_ptr<SceneResourceManager> newSceneResourceManager)
{
	sceneResourceManager = newSceneResourceManager;
}


SceneTextureResourceManager::~SceneTextureResourceManager()
{

}

//	Process the Scene Resource Request.
void SceneTextureResourceManager::processRequest(std::shared_ptr<SceneResourceRequest> newResourceRequest)
{
	
}

