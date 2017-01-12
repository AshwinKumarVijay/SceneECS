#include "RTSModule.h"

#include "../../RenderableManager/RenderableManager.h"

#include "../../Renderer/Renderer.h"
#include "../../ModuleRenderer/ModuleRenderer.h"

#include "../Camera/Camera.h"

#include "../../Renderer/SceneMetaData.h"
#include "../../RendererResourceManagers/RendererShaderManager/RendererShaderData/RendererShaderData.h"

//	Default RTSModule Constructor.
RTSModule::RTSModule(std::shared_ptr<Renderer> newModuleRenderer, const unsigned int & newSourceTextureID) : RendererModule(newModuleRenderer)
{
	sourceTextureID = newSourceTextureID;

	//	Add the Shader Type.
	std::shared_ptr<RendererShaderData> newRendererShaderData = std::make_shared<RendererShaderData>();
	newRendererShaderData->addPropertyValue("Shader Type", "HDR Shader");

	//	Set the Vertex Shader HDR Source.
	std::string vsSource = "Assets/ModuleRendererShaders/PostProcessShaders/HDRShaders/HDR.vert.glsl";
	newRendererShaderData->addPropertyValue("Vertex Shader Source", vsSource);

	//	Set the Fragment Shader HDR Source.
	std::string fsSource = "Assets/ModuleRendererShaders/PostProcessShaders/HDRShaders/HDR.frag.glsl";
	newRendererShaderData->addPropertyValue("Fragment Shader Source", fsSource);

	//	Add the RendererShaderData to the Module Renderer.
	newModuleRenderer->addShader(newRendererShaderData);
}


//	Default RTSModule Destructor.
RTSModule::~RTSModule()
{

}

//	Render to Screen.
void RTSModule::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	//	Get the Renderer.
	std::weak_ptr<Renderer> weakRenderer = getRenderer();

	//	Get the Module Renderer.
	std::shared_ptr<ModuleRenderer> moduleRenderer = std::dynamic_pointer_cast<ModuleRenderer>(weakRenderer.lock());

	//	
	glViewport(0, 0, moduleRenderer->getSceneQuality().screenWidth, moduleRenderer->getSceneQuality().screenHeight);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	Get the associated Shader Data.
	std::shared_ptr<const RendererShaderData> hdrShaderData = moduleRenderer->getShaderManager()->viewShaderData("HDR Shader");

	glUseProgram(hdrShaderData->getShaderID());

	//	Upload the Source Texture.
	moduleRenderer->uploadPrimaryPostProcessTextures(*hdrShaderData, sourceTextureID, 0, 0, 0);

	//	Draw the Arrays.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
