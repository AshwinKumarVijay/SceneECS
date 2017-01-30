#include "ShadowsModule.h"
#include "../LightsModule/LightsModule.h"

//	Default ShadowsModule Constructor.
ShadowsModule::ShadowsModule(std::shared_ptr<Renderer> newModuleRenderer, std::shared_ptr<const LightsModule> newLightsModule) : RendererModule(newModuleRenderer)
{
	//	
	lightsModule = newLightsModule;

	//	Create Shadows Textures And Framebuffers.
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

//	View the Light Shadows Module Meta Datas.
const std::vector<LightShadowsModuleMetaData>& ShadowsModule::viewLightShadowsModuleMetaDatas() const
{
	return lightShadowsModuleMetaDatas;
}

//	
void ShadowsModule::createShadowsTexturesAndFramebuffers()
{
	const std::vector<LightModuleMetaData> lightModuleMetaDatas = lightsModule.lock()->viewLightModuleMetaDatas();

	//	Iterate over the Light Module MetaDatas.
	for (int i = 0; i < lightModuleMetaDatas.size(); i++)
	{
		unsigned int newFramebufferObject = 0;

		//	Generate the new Framebuffer Object.
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

		//	Create the Light Shadows Module MetaData.
		LightShadowsModuleMetaData newShadowModule;

		// Associate the Light Framebuffer Object.
		newShadowModule.lightFramebufferObject = newFramebufferObject;

		//	Add the Light Module Meta Datas.
		lightShadowsModuleMetaDatas.push_back(newShadowModule);
	}
}
