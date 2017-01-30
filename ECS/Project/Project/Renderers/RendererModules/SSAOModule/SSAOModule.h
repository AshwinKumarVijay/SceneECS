#pragma once

#include "../RendererModule.h"

class RendererShaderData;

class SSAOModule : public RendererModule
{

public:

	//	Default SAAOModule Constructor.
	SSAOModule(std::shared_ptr<Renderer> newRenderer, unsigned int worldSpacePositionTextureID, unsigned int worldSpaceVertexNormalAndDepthTextureID, unsigned int ambientColorTexture, unsigned int ambientDepthTexture);

	//	Default SSAOModule Destructor.
	virtual ~SSAOModule();

	//	Render.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

private:

	//	Create the SSAO Framebuffers And Textures.
	virtual void createSSAOFramebuffersAndTextures();

	//	The Ambient Occlusion Framebuffer ID.
	unsigned int ambientOcclusionFramebufferID;

	//	The Color Texture Resulting from the Ambient Occlusion Pass.
	unsigned int ambientOcclusionPassColorTexture;

	//	The Depth Texture Resulting from the Ambient Occlusion Pass.
	unsigned int ambientOcclusionPassDepthTexture;

	//	Screen Width and Screen Height being of the screen being rendered to.
	unsigned int screenWidth, screenHeight;

	//	The Deferred Pass Lighting Shader.
	std::shared_ptr<RendererShaderData> ssaoShader;

};

