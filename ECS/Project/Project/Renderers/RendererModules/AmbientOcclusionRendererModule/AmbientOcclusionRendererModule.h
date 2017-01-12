#pragma once

class AmbientOcclusionRendererModule
{

public:

	//	Default Ambient Occlusion Renderer Module Constructor.
	AmbientOcclusionRendererModule();

	//	Default Ambient Occlusion Renderer Module Destructor.
	virtual ~AmbientOcclusionRendererModule();


private:

	//	The Ambient Occlusion Framebuffer ID.
	unsigned int ambientOcclusionFramebufferID;

	//	The Color Texture Resulting from the Ambient Occlusion Pass.
	unsigned int ambientOcclusionPassColorTexture;

	//	The Depth Texture Resulting from the Ambient Occlusion Pass.
	unsigned int ambientOcclusionPassDepthTexture;
};

