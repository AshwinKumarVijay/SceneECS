#include "ShadowsModule.h"
#include "../LightsModule/LightsModule.h"

//	Default ShadowsModule Constructor.
ShadowsModule::ShadowsModule(std::shared_ptr<Renderer> newModuleRenderer, std::shared_ptr<const LightsModule> newLightsModule) : RendererModule(newModuleRenderer)
{
	lightsModule = newLightsModule;
	createShadowsTexturesAndFramebuffers();
}

//	Default ShadowsModule Destructor.
ShadowsModule::~ShadowsModule()
{

}

//	Render the Shadows to the Shadow Maps.
void ShadowsModule::render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera)
{
	const std::vector<LightModuleMetaData> lightModuleMetaDatas = lightsModule.lock()->viewLightModuleMetaDatas();

	for (int i = 0; i < lightModuleMetaDatas.size(); i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, lightShadowsModuleMetaDatas[i].lightFramebufferObject);

		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

const std::vector<LightShadowsModuleMetaData>& ShadowsModule::viewLightShadowsModuleMetaDatas() const
{
	return lightShadowsModuleMetaDatas;
}

//	
void ShadowsModule::createShadowsTexturesAndFramebuffers()
{
	const std::vector<LightModuleMetaData> lightModuleMetaDatas = lightsModule.lock()->viewLightModuleMetaDatas();

	for (int i = 0; i < lightModuleMetaDatas.size(); i++)
	{
		unsigned int newFramebufferObject = 0;
		glGenFramebuffers(1, &newFramebufferObject);
		glBindFramebuffer(GL_FRAMEBUFFER, newFramebufferObject);

		//	Associate the Color Texture with the Current Framebuffer.
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, lightModuleMetaDatas[i].lightColorMap, 0);

		//	Associate the Depth Stencil Texture with the Current Framebuffer.
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, lightModuleMetaDatas[i].lightDepthMap, 0);

		//	Set the Draw Buffers of the Current Framebuffer.
		GLenum framebufferDrawBuffers[] = { GL_COLOR_ATTACHMENT0 + 0};
		glDrawBuffers(1, framebufferDrawBuffers);

		//	Bind the Default Framebuffer.
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//	Add the Light Shadows Module.
		LightShadowsModuleMetaData newShadowModule;
		newShadowModule.lightFramebufferObject = newFramebufferObject;
		lightShadowsModuleMetaDatas.push_back(newShadowModule);

	}
}
