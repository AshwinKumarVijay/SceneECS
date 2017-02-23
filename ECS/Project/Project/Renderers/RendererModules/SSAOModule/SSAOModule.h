#pragma once

#include "../RendererModule.h"

class RendererShaderData;
class Sampler;

class SSAOModule : public RendererModule
{

public:

	//	Default SAAOModule Constructor.
	SSAOModule(std::shared_ptr<Renderer> newRenderer, unsigned int newWorldSpacePositionTexture, unsigned int newWorldSpaceVertexNormalAndDepthTexture, unsigned int newAmbientPassColorTexture, unsigned int newAmbientPassDepthTexture);

	//	Default SSAOModule Destructor.
	virtual ~SSAOModule();

	//	Render.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

	//	Return the Ambient Occlusion Pass Color Texture.
	virtual unsigned int viewAmbientOcclusionPassColorTexture() const;

	//	Return the Ambient Occlusion Pass Depth Texture.
	virtual unsigned int viewAmbientOcclusionPassDepthTexture() const;

	//	Return the Sampling Parameters.
	virtual void uploadSamplingParameters();

private:

	//	Create the SSAO Framebuffers And Textures.
	virtual void createSSAOTexturesAndFramebuffers();

	//	The Ambient Occlusion Framebuffer ID.
	unsigned int ambientOcclusionFramebuffer;

	//	The Color Texture Resulting from the Ambient Occlusion Pass.
	unsigned int ambientOcclusionPassColorTexture;

	//	The Depth Texture Resulting from the Ambient Occlusion Pass.
	unsigned int ambientOcclusionPassDepthTexture;

	//	Screen Width and Screen Height being of the screen being rendered to.
	unsigned int screenWidth, screenHeight;

	//	SSAO Quality.
	unsigned int ssaoQuality, ssaoSampleCount;

	//	World Space Vertex Position.
	unsigned int worldSpaceVertexPositionTexture;

	//	World Space Vertex Normal And Depth Texture.
	unsigned int worldSpaceVertexNormalAndDepthTexture;

	//	Ambient Color Texture.
	unsigned int ambientColorPassTexture;

	//	Ambient Depth Texture.
	unsigned int ambientDepthPassTexture;

	//	The Deferred Pass Lighting Shader.
	std::shared_ptr<RendererShaderData> ssaoShader;

	//	The SSAO Sampler.
	std::shared_ptr<Sampler> ssaoSampler;


};

