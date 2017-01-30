#pragma once
#include <memory>
#include "../RendererModule.h"

class RenderableManager;

class Renderer;
class ModuleRenderer;

class Camera;

struct SceneQuality;

class GBufferModule : public RendererModule
{

public:

	//	Default GBufferModule Constructor.
	GBufferModule(std::shared_ptr<Renderer> newRenderer);

	//	Default GBufferModule Destructor.
	virtual ~GBufferModule();

	//	Render to the GBuffer.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Return the World Space Position Texture ID.
	unsigned int viewWorldSpacePositionTexture() const;

	//	Return the World Space Vertex Normal and Depth Texture ID.
	unsigned int viewWorldSpaceVertexNormalAndDepthTexture() const;

	//	Return the Ambient Color Texture ID.
	unsigned int viewAmbientColorTexture() const;

	//	Return the Diffuse Albedo and Lit Type Texture ID.
	unsigned int viewDiffuseAlbedoAndLitTypeTexture() const;

	//	Return the Specular Albedo and Lighting Type Texture ID.
	unsigned int viewSpecularAlbedoAndLightingTypeTexture() const;

	//	Return the Material, Roughness, Fresnel, Opacity Texture ID.
	unsigned int viewMRFOTexture() const;

	//	Return the Emissive Color And Intensity Texture ID.
	unsigned int viewEmissiveColorAndIntensityTexture() const;

	//	Return the Depth Texture ID.
	unsigned int viewDepthTexture() const;

private:

	//	Create the G Buffer Shaders.
	virtual void createGBufferShaders(std::shared_ptr<Renderer> newModuleRenderer);

	virtual void createBasicGBufferShader(std::shared_ptr<Renderer> newModuleRenderer);
	virtual void createDiffuseTextureGBufferShader(std::shared_ptr<Renderer> newModuleRenderer);
	virtual void createSpecularTextureGBufferShader(std::shared_ptr<Renderer> newModuleRenderer);
	virtual void createDiffuseSpecularTexturesGBufferShader(std::shared_ptr<Renderer> newModuleRenderer);

	//	Create the G Buffer Textures and Framebuffers.
	virtual void createGBufferTexturesAndFramebuffers(const unsigned int & screenWidth, const unsigned int & screenHeight);

	//	World Space Vertex Position Texture.
	unsigned int worldSpaceVertexPositionTexture;

	//	World Space Vertex Normal and Depth Texture.
	unsigned int worldSpaceVertexNormalAndDepthTexture;

	//	Ambient Color Texture.
	unsigned int ambientColorTexture;

	//	Diffuse Albedo and Lit Type Texture.
	unsigned int diffuseAlbedoAndLitTypeTexture;

	//	Specular Albedo and Lighting Type Texture.
	unsigned int specularAlbedoAndLightingTypeTexture;

	//	Metallicness, Roughness, Fresnel, Opacity Texture
	unsigned int mrfoTexture;

	//	Emissive Color and Intensity Texture.
	unsigned int emissiveColorAndIntensityTexture;

	//	Depth Texture.
	unsigned int depthTexture;

	//	Render to G Buffer Framebuffer ID.
	unsigned int framebufferID;
};

