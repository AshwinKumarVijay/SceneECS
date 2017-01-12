#pragma once
#include <memory>
#include "../RendererModule.h"

class Renderer;
class ModuleRenderer;

class GBufferModule;
class LightsModule;

class RendererShaderData;
class Camera;

class DPassLightingModule : public RendererModule
{

public:

	//	Default DPassLightingModule Constructor.
	DPassLightingModule(std::shared_ptr<Renderer> newModuleRenderer, std::shared_ptr<const GBufferModule> newGBufferModule, std::shared_ptr<const LightsModule> newLightsModule);

	//	Default DPassLightingModule Destructor.
	virtual ~DPassLightingModule();

	//	Render the Deferred Pass Lighting Module.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Return the Deferred Pass Lighting Color Texture.
	unsigned int viewDeferredPassLightingColorTexture();

	//	Return the Deferred Pass Lighting Depth Texture.
	unsigned int viewDeferredPassLightingDepthTexture();

private:

	//	Create the Deferred Pass Lighting Textures And Framebuffers.
	virtual void createDeferredPassLightingTexturesAndFramebuffers();

	//	Deferred Pass Lighting Color Texture.
	unsigned int deferredPassLightingModuleColorTexture;

	//	Deferred Pass Lighting Depth Texture.
	unsigned int deferredPassLightingModuleDepthTexture;

	//	Deferred Pass Framebuffer Object.
	unsigned int deferredPassLightingFramebufferObject;

	//	Screen Width and Screen Height.
	unsigned int screenWidth, screenHeight;

	//	The Deferred Pass Lighting Shader.
	std::shared_ptr<RendererShaderData> deferredPassLightingShader;

	//	The G Buffer Module.
	std::weak_ptr<const GBufferModule> gBufferModule;

	//	The Lights Module.
	std::weak_ptr<const LightsModule> lightsModule;

};

