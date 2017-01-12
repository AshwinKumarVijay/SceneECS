#include "GBufferModule.h"

#include "../../RenderableManager/RenderableManager.h"

#include "../../Renderer/Renderer.h"
#include "../../ModuleRenderer/ModuleRenderer.h"

#include "../../RendererResourceManagers/RendererShaderManager/RendererShaderData/RendererShaderData.h"

#include "../Camera/Camera.h"

#include "../../Renderer/SceneMetaData.h"


//	Default GBufferModule Constructor.
GBufferModule::GBufferModule(std::shared_ptr<Renderer> newModuleRenderer) : RendererModule(newModuleRenderer)
{
	//	Create the G Buffer Textures and Framebuffers using the provided Scene Width and Scene Height.
	createGBufferTexturesAndFramebuffers(newModuleRenderer->getSceneQuality().screenWidth, newModuleRenderer->getSceneQuality().screenHeight);

	//	Add the Shader Type.
	std::shared_ptr<RendererShaderData> newRendererShaderData = std::make_shared<RendererShaderData>();
	newRendererShaderData->addPropertyValue("Shader Type", "Basic Deferred G Buffer Shader");
	newRendererShaderData->addPropertyValue("Renderable Shader Type", "OPAQUE_BASIC");
	newRendererShaderData->addPropertyValue("Shader Output Opacity", "False");
	newRendererShaderData->addPropertyValue("Require Vertex Basic Data", "True");

	//	Set the Vertex Shader G Buffer Source.
	std::string vsSource = "Assets/ModuleRendererShaders/DeferredGBufferPassShaders/BasicGBufferShaders/BasicGBufferShader.vert.glsl";
	newRendererShaderData->addPropertyValue("Vertex Shader Source", vsSource);

	//	Set the Fragment Shader G Buffer Source.
	std::string fsSource = "Assets/ModuleRendererShaders/DeferredGBufferPassShaders/BasicGBufferShaders/BasicGBufferShader.frag.glsl";
	newRendererShaderData->addPropertyValue("Fragment Shader Source", fsSource);

	//	Add the RendererShaderData to the Module Renderer.
	newModuleRenderer->addShader(newRendererShaderData);
}

//	Default GBufferModule Destructor.
GBufferModule::~GBufferModule()
{

}

//	Render to the G Buffer Textures.
void GBufferModule::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	//	Get the Renderer.
	std::weak_ptr<Renderer> weakRenderer = getRenderer();

	//	Get the Module Renderer.
	std::shared_ptr<ModuleRenderer> moduleRenderer = std::dynamic_pointer_cast<ModuleRenderer>(weakRenderer.lock());

	//	
	glViewport(0, 0, moduleRenderer->getSceneQuality().screenWidth, moduleRenderer->getSceneQuality().screenHeight);

	//	Bind the G-Buffer Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

	//	Clear the Color and Depth Buffer.
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	Render all the objects having a Material with no Transparency.

	//	Get the Renderable Batch Types.
	const std::set<RenderableTypeBatchMetaData> & renderableBatchTypes = moduleRenderer->getRenderableManager()->getRenderableTypeBatchMetaDatas();

	//	Iterate over the Renderable Types.
	for (auto currentRenderableType = renderableBatchTypes.begin(); currentRenderableType != renderableBatchTypes.end(); currentRenderableType++)
	{
		//	Check if this is a Valid Renderable Type.
		if (currentRenderableType->renderableTypeBatch->getIsValidRenderableType())
		{
			//	Get the Current Renderer Shader Data.
			std::shared_ptr<const RendererShaderData> currentRendererShaderData = moduleRenderer->getRendererShaderDataForRenderableShadingType(currentRenderableType->renderableType.shaderType);

			//	Set the Active Shader.
			glUseProgram(currentRendererShaderData->getShaderID());

			//	Upload the Camera Data.
			moduleRenderer->uploadCameraData(*currentRendererShaderData, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));
			
			//	Get the Renderer Shader Type.
			std::string rendererShaderType;
			if (!currentRendererShaderData->getPropertyValue("Shader Type", rendererShaderType))
			{
				throw "Error! GBufferModule: Render -> No Available Shader Type!";
			}

			//	Get the Renderer Shader Output Opacity.
			std::string rendererShaderOutputOpacity;
			if (!currentRendererShaderData->getPropertyValue("Shader Output Opacity", rendererShaderOutputOpacity))
			{
				throw "Error! GBufferModule: Render -> No Available Shader Output Opacity Type!";
			}


			//	Check whether the Material is Transparent.
			if (rendererShaderOutputOpacity != "True")
			{
				//	Render the Renderables that use the Shader Data specified by the Renderer.
				moduleRenderer->renderRenderablesOfShaderType(currentRenderableType->renderableType.shaderType, *currentRendererShaderData, activeCamera->getViewMatrix(), deltaFrameTime, currentFrameTime, lastFrameTime);
			}
		}
	}

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//	Return the World Space Position Texture.
unsigned int GBufferModule::viewWorldSpacePositionTexture() const
{
	return worldSpaceVertexPositionTexture;
}

//	Return the World Space Vertex Normal and Depth Texture.
unsigned int GBufferModule::viewWorldSpaceVertexNormalAndDepthTexture() const
{
	return worldSpaceVertexNormalAndDepthTexture;
}

//	Return the Ambient Color Texture.
unsigned int GBufferModule::viewAmbientColorTexture() const
{
	return ambientColorTexture;
}

//	Return the Diffuse Albedo and Lit Type Texture.
unsigned int GBufferModule::viewDiffuseAlbedoAndLitTypeTexture() const
{
	return diffuseAlbedoAndLitTypeTexture;
}

//	Return the Specular Albedo and Lighting Type Texture.
unsigned int GBufferModule::viewSpecularAlbedoAndLightingTypeTexture() const
{
	return specularAlbedoAndLightingTypeTexture;
}

//	Return the MRFO Texture.
unsigned int GBufferModule::viewMRFOTexture() const
{
	return mrfoTexture;
}

//	Return the Emssive Color and Intensity Texture.
unsigned int GBufferModule::viewEmissiveColorAndIntensityTexture() const
{
	return emissiveColorAndIntensityTexture;
}

//	Return the Depth Texture.
unsigned int GBufferModule::viewDepthTexture() const
{
	return depthTexture;
}

//	Create the G Buffer Textures and Framebuffers.
void GBufferModule::createGBufferTexturesAndFramebuffers(const unsigned int & screenWidth, const unsigned int & screenHeight)
{
	//	Generate the World Space Vertex Position Textures.
	glGenTextures(1, &worldSpaceVertexPositionTexture);
	glBindTexture(GL_TEXTURE_2D, worldSpaceVertexPositionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the World space Vertex Normal and Depth Texture.
	glGenTextures(1, &worldSpaceVertexNormalAndDepthTexture);
	glBindTexture(GL_TEXTURE_2D, worldSpaceVertexNormalAndDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Ambient Color Texture.
	glGenTextures(1, &ambientColorTexture);
	glBindTexture(GL_TEXTURE_2D, ambientColorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Diffuse Albedo and Lit Type Texture.
	glGenTextures(1, &diffuseAlbedoAndLitTypeTexture);
	glBindTexture(GL_TEXTURE_2D, diffuseAlbedoAndLitTypeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Specular Albedo and Lighting Type Texture.
	glGenTextures(1, &specularAlbedoAndLightingTypeTexture);
	glBindTexture(GL_TEXTURE_2D, specularAlbedoAndLightingTypeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Specular Albedo and Lighting Type Texture.
	glGenTextures(1, &mrfoTexture);
	glBindTexture(GL_TEXTURE_2D, mrfoTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Emssive Color and Intensity Texture.
	glGenTextures(1, &emissiveColorAndIntensityTexture);
	glBindTexture(GL_TEXTURE_2D, emissiveColorAndIntensityTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Depth Texture.
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);


	//	Create the Framebuffer to Render to the G Buffer.
	glGenFramebuffers(1, &framebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

	//	Associate the Textures of the G Buffer with the G Buffer Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, worldSpaceVertexPositionTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 1, GL_TEXTURE_2D, worldSpaceVertexNormalAndDepthTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 2, GL_TEXTURE_2D, ambientColorTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 3, GL_TEXTURE_2D, diffuseAlbedoAndLitTypeTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 4, GL_TEXTURE_2D, specularAlbedoAndLightingTypeTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 5, GL_TEXTURE_2D, mrfoTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 6, GL_TEXTURE_2D, emissiveColorAndIntensityTexture, 0);

	//	Associate the Depth Stencil Texture with the G Buffer Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	//	Set up the G Buffer Draw Textures.
	GLenum framebufferDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0, GL_COLOR_ATTACHMENT0 + 1, GL_COLOR_ATTACHMENT0 + 2, GL_COLOR_ATTACHMENT0 + 3, GL_COLOR_ATTACHMENT0 + 4, GL_COLOR_ATTACHMENT0 + 5, GL_COLOR_ATTACHMENT0 + 6};
	glDrawBuffers(7, framebufferDrawBuffers);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
