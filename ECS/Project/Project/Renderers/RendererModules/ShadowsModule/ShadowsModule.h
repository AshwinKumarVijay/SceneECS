#pragma once
#include <memory>
#include <array>
#include "../RendererModule.h"

class RenderableManager;
class Renderer;
class ModuleRenderer;
class Camera;

struct RendererLightData;
struct SceneQuality;

class LightsModule;

struct LightShadowsModuleMetaData
{
	unsigned int lightFramebufferObject;
};

class ShadowsModule : public RendererModule
{

public:

	//	Default ShadowsModule Constructor.
	ShadowsModule(std::shared_ptr<Renderer> newModuleRenderer, std::shared_ptr<const LightsModule> newLightsModule);

	//	Default ShadowsModule Destructor.
	virtual ~ShadowsModule();

	//	Render the Shadows to the Shadow Maps.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);


	//	Return the Light Module Meta Datas.
	virtual const std::vector<LightShadowsModuleMetaData> & viewLightShadowsModuleMetaDatas() const;

private:

	//	Create the Textures and Framebuffers for Shadow Rendering.	
	virtual void createShadowsTexturesAndFramebuffers();

	//	
	std::weak_ptr<const LightsModule> lightsModule;

	//	Data for Rendering Shadows from a Point Light.	
	unsigned int pointLightCubeColorTexture;
	unsigned int pointLightCubeDepthTexture;
	std::array<unsigned int, 6> pointLightFramebufferObjects;

	//	Data for Rendering Shadows from a Directional Light.
	unsigned int directionalLightColorTexture;
	unsigned int directionalLightDepthTexture;
	unsigned int directionalLightFramebufferObject;

	//	Data for Rendering Shadows from a Spot Light
	unsigned int spotLightColorTexture;
	unsigned int spotLightDepthTexture;
	unsigned int spotLightFramebufferObject;


	std::vector<LightShadowsModuleMetaData> lightShadowsModuleMetaDatas;
};

