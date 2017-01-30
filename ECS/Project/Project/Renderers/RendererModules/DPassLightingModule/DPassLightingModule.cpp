#include "DPassLightingModule.h"
#include "../Renderers/ModuleRenderer/ModuleRenderer.h"

#include "../GBufferModule/GBufferModule.h"
#include "../LightsModule/LightsModule.h"

#include "../../../Camera/Camera.h"

#include "../../RendererResourceManagers/RendererShaderManager/RendererShaderData/RendererShaderData.h"

//	Default DPassLightingModule Constructor.
DPassLightingModule::DPassLightingModule(std::shared_ptr<Renderer> newRenderer, std::shared_ptr<const GBufferModule> newGBufferModule, std::shared_ptr<const LightsModule> newLightsModule) : RendererModule(newRenderer)
{
	//	Copy over the Screen Width and Screen Height Textures.
	screenWidth = newRenderer->getSceneQuality().screenWidth;
	screenHeight = newRenderer->getSceneQuality().screenHeight;

	//	Copy over the G Buffer Module.
	gBufferModule = newGBufferModule;
	
	//	Copy over the Lights Module.
	lightsModule = newLightsModule;

	//	Create the Deferred Pass Lighting Shader.
	deferredPassLightingShader = std::make_shared<RendererShaderData>();

	//	Add the Property Value.
	deferredPassLightingShader->addPropertyValue("Shader Type", "Deferred Lighting Pass Shader");
	deferredPassLightingShader->addPropertyValue("Shader Output Opacity", "False");

	//	Set the Vertex Shader G Buffer Source.
	std::string vsSource = "Assets/ModuleRendererShaders/DeferredLightingPassShaders/PhongLightingPassShaders/PhongLightingShader.vert.glsl";
	deferredPassLightingShader->addPropertyValue("Vertex Shader Source", vsSource);

	//	Set the Fragment Shader G Buffer Source.
	std::string fsSource = "Assets/ModuleRendererShaders/DeferredLightingPassShaders/PhongLightingPassShaders/PhongLightingShader.frag.glsl";
	deferredPassLightingShader->addPropertyValue("Fragment Shader Source", fsSource);

	//	Add the Shader to the Module Renderer.
	newRenderer->addShader(deferredPassLightingShader);

	//	
	createDeferredPassLightingTexturesAndFramebuffers();
}


//	Default DPassLightingModule Destructor.
DPassLightingModule::~DPassLightingModule()
{

}

//	Render the Deferred Pass Lighting Module.
void DPassLightingModule::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	//	Use the Program.
	glUseProgram(deferredPassLightingShader->getShaderID());

	//	Bind the Deferred Pass Lighting Framebuffer Object.
	glBindFramebuffer(GL_FRAMEBUFFER, deferredPassLightingFramebufferObject);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	
	std::shared_ptr<ModuleRenderer> moduleRenderer = std::dynamic_pointer_cast<ModuleRenderer>(getRenderer().lock());

	//	Upload the Ambient Light Data.
	moduleRenderer->uploadAmbientLightData(*deferredPassLightingShader);

	//	Upload the Camera Data.
	moduleRenderer->uploadCameraData(*deferredPassLightingShader, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));

	//	Upload the G Buffer Textures.
	moduleRenderer->uploadGBufferTextures(*deferredPassLightingShader, gBufferModule.lock()->viewWorldSpacePositionTexture(), gBufferModule.lock()->viewWorldSpaceVertexNormalAndDepthTexture(), gBufferModule.lock()->viewAmbientColorTexture(), gBufferModule.lock()->viewDiffuseAlbedoAndLitTypeTexture(), gBufferModule.lock()->viewSpecularAlbedoAndLightingTypeTexture(), gBufferModule.lock()->viewMRFOTexture(), gBufferModule.lock()->viewEmissiveColorAndIntensityTexture(), 0);

	//	Upload the Lights Data.
	lightsModule.lock()->uploadLightsData(deferredPassLightingShader);

	//	Draw the Arrays.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//	Create the Deferred Pass Lighting Textures And Framebuffers.
void DPassLightingModule::createDeferredPassLightingTexturesAndFramebuffers()
{
	//	Create the Deferred Pass Lighting Module Color Texture.
	glGenTextures(1, &deferredPassLightingModuleColorTexture);
	glBindTexture(GL_TEXTURE_2D, deferredPassLightingModuleColorTexture);
	glTextureImage2DEXT(deferredPassLightingModuleColorTexture, GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTextureParameteri(deferredPassLightingModuleColorTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(deferredPassLightingModuleColorTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);


	//	Create the Deferred Pass Lighting Module Depth Texture.
	glGenTextures(1, &deferredPassLightingModuleDepthTexture);
	glBindTexture(GL_TEXTURE_2D, deferredPassLightingModuleDepthTexture);
	glTextureImage2DEXT(deferredPassLightingModuleDepthTexture, GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTextureParameteri(deferredPassLightingModuleDepthTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(deferredPassLightingModuleDepthTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);


	//	Bind the Deferred Pass Lighting Framebuffer Object
	glGenFramebuffers(1, &deferredPassLightingFramebufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, deferredPassLightingFramebufferObject);

	//	Associate the Color Texture with the Current Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, deferredPassLightingModuleColorTexture, 0);

	//	Associate the Depth Stencil Texture with the Current Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, deferredPassLightingModuleDepthTexture, 0);

	//	Set the Draw Buffers of the Current Framebuffer.
	GLenum framebufferDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0 };
	glDrawBuffers(1, framebufferDrawBuffers);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//	Return the Deferred Pass Lighting Color Texture.
unsigned int DPassLightingModule::viewDeferredPassLightingColorTexture()
{
	return deferredPassLightingModuleColorTexture;
}

//	Return the Deferred Pass Lighting Depth Texture.
unsigned int DPassLightingModule::viewDeferredPassLightingDepthTexture()
{
	return deferredPassLightingModuleDepthTexture;
}
