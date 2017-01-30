#pragma once
#include "../RendererModule.h"

class Camera;

struct SceneQuality;

class RTSModule : public RendererModule
{

public:

	//	Default RTSModule Constructor.
	RTSModule(std::shared_ptr<Renderer> newRenderer, const unsigned int & newSourceTextureID);

	//	Default RTSModule Destructor.
	virtual ~RTSModule();

	//	Render to the Screen.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera);

private:

	//	The Source Texture to Render to the Screen.
	unsigned int sourceTextureID;
};

