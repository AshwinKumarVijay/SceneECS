#include "SSAOModule.h"
#include "../../Renderer/Renderer.h"
#include "../../ModuleRenderer/ModuleRenderer.h"
#include "../../RenderableManager/RenderableManager.h"
#include "../../Renderer/SceneMetaData.h"
#include "../../RendererResourceManagers/RendererShaderManager/RendererShaderData/RendererShaderData.h"
#include "../../Sampler/Sampler.h"

#include "../../../Camera/Camera.h"

//	Default Ambient Occlusion Renderer Module Constructor.
SSAOModule::SSAOModule(std::shared_ptr<Renderer> newRenderer, unsigned int newWorldSpaceVertexPositionTexture, unsigned int newWorldSpaceVertexNormalAndDepthTexture, unsigned int newAmbientPassColorTexture, unsigned int newAmbientPassDepthTexture) : RendererModule(newRenderer)
{
	//	Get the Module Renderer.
	std::shared_ptr<ModuleRenderer> moduleRenderer = std::dynamic_pointer_cast<ModuleRenderer>(newRenderer);

	//	Copy over the Screen Width and Screen Height Textures.
	screenWidth = moduleRenderer->getSceneQuality().screenWidth;
	screenHeight = moduleRenderer->getSceneQuality().screenHeight;

	//	Create the SSAO Shader.
	ssaoShader = std::make_shared<RendererShaderData>();

	//	Add the Property Value.
	ssaoShader->addPropertyValue("Shader Type", "SSAO Shader");
	ssaoShader->addPropertyValue("Shader Output Opacity", "False");

	//	Set the Vertex Shader G Buffer Source.
	std::string vsSource = "Assets/ModuleRendererShaders/SSAOShaders/SSAO.vert.glsl";
	ssaoShader->addPropertyValue("Vertex Shader Source", vsSource);

	//	Set the Fragment Shader G Buffer Source.
	std::string fsSource = "Assets/ModuleRendererShaders/SSAOShaders/SSAO.frag.glsl";
	ssaoShader->addPropertyValue("Fragment Shader Source", fsSource);

	//	Add the Shader.
	newRenderer->addShader(ssaoShader);

	//	Create the SSAO Framebuffers and Textures.
	createSSAOTexturesAndFramebuffers();

	worldSpaceVertexPositionTexture = newWorldSpaceVertexPositionTexture;
	worldSpaceVertexNormalAndDepthTexture = newWorldSpaceVertexNormalAndDepthTexture;
	ambientColorPassTexture = newAmbientPassColorTexture;
	ambientDepthPassTexture = newAmbientPassDepthTexture;

	//	Create the Sampler.
	ssaoQuality = moduleRenderer->getSceneQuality().ssaoQuality;
	ssaoSampleCount = (unsigned int)(pow(2, ssaoQuality));
	ssaoSampler = std::make_shared<Sampler>(ssaoSampleCount);
	
}


//	Default Ambient Occlusion Renderer Module Destructor.
SSAOModule::~SSAOModule()
{


}
//	Render.
void SSAOModule::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	//	Bind the Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, ambientOcclusionFramebuffer);

	glUseProgram(ssaoShader->getShaderID());

	//	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	Get the Renderer.
	std::shared_ptr<ModuleRenderer> moduleRenderer = std::dynamic_pointer_cast<ModuleRenderer>(getRenderer().lock());

	//	Upload the Camera Data.
	moduleRenderer->uploadCameraData(*ssaoShader, glm::vec4(activeCamera->getCameraPosition(), 1.0), activeCamera->getPerspectiveMatrix(), activeCamera->getViewMatrix(), glm::vec4(activeCamera->getNearClip(), activeCamera->getFarClip(), 0.0, 0.0));

	//	Upload the Primary Post Process Textures.
	moduleRenderer->uploadPrimaryPostProcessTextures(*ssaoShader, worldSpaceVertexPositionTexture, worldSpaceVertexNormalAndDepthTexture, ambientColorPassTexture, ambientDepthPassTexture);

	uploadSamplingParameters();

	//	Upload the Noise Textures.
	moduleRenderer->uploadNoiseTextures(*ssaoShader);
	
	//	Render the SSAO Pass.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//	Return the Ambient Occlusion Pass Color Texture.
unsigned int SSAOModule::viewAmbientOcclusionPassColorTexture() const
{
	return ambientOcclusionPassColorTexture;
}

//	Return the Ambient Occlusion Pass Depth Texture.
unsigned int SSAOModule::viewAmbientOcclusionPassDepthTexture() const
{
	return ambientOcclusionPassDepthTexture;
}

//	Upload the Sampling Parameters.
void SSAOModule::uploadSamplingParameters()
{
	//	Upload the Hemisphere Samples.
	int u_hemisphereSamples = -1;
	if (ssaoShader->getUniformLocation("u_hemisphereSamples", u_hemisphereSamples))
	{
		glUniform4fv(u_hemisphereSamples, (int)ssaoSampler->viewHemisphereKernel().size(), glm::value_ptr(*ssaoSampler->viewHemisphereKernel().data()));
	}


	//	Upload the Hemisphere Radius.
	int u_hemisphereRadius = -1;
	if (ssaoShader->getUniformLocation("u_hemisphereRadius", u_hemisphereRadius))
	{
		glUniform1f(u_hemisphereRadius, 4.0f);
	}
}

//	Create the SSAO Framebuffers and Textures.
void SSAOModule::createSSAOTexturesAndFramebuffers()
{
	//	Active Texture 0.
	glActiveTexture(GL_TEXTURE0 + 0);

	//	Generate the Ambient Occlussion Pass Color Texture.
	glGenTextures(1, &ambientOcclusionPassColorTexture);
	glBindTexture(GL_TEXTURE_2D, ambientOcclusionPassColorTexture);
	glTextureImage2DEXT(ambientOcclusionPassColorTexture, GL_TEXTURE_2D, 0, GL_RGBA32F, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTextureParameteri(ambientOcclusionPassColorTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(ambientOcclusionPassColorTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	//	Generate the Ambient Occlussion Pass Depth Texture.
	glGenTextures(1, &ambientOcclusionPassDepthTexture);
	glBindTexture(GL_TEXTURE_2D, ambientOcclusionPassDepthTexture);
	glTextureImage2DEXT(ambientOcclusionPassDepthTexture, GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTextureParameteri(ambientOcclusionPassDepthTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(ambientOcclusionPassDepthTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);


	//	Generate the Ambient Occlusion Framebuffer ID.
	glGenFramebuffers(1, &ambientOcclusionFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, ambientOcclusionFramebuffer);

	//	Associate the Color Texture with the Current Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, ambientOcclusionPassColorTexture, 0);

	//	Associate the Depth Stencil Texture with the Current Framebuffer.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, ambientOcclusionPassDepthTexture, 0);

	//	Set the Draw Buffers of the Current Framebuffer.
	GLenum framebufferDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0 };
	glDrawBuffers(1, framebufferDrawBuffers);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

