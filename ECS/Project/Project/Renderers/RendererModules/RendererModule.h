#pragma once
#include <vector>
#include <memory>
#include "GL\glew.h"

class Renderer;
class ModuleRenderer;

class Camera;

//
class RendererModule
{

public:
	
	//	Default RendererModule Constructor.
	RendererModule(std::shared_ptr<Renderer> newRenderer);

	//	Default RendererModule Destructor.
	virtual ~RendererModule();

	//	Render the Module.
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> activeCamera) = 0;

	//	Return the weak_ptr to the Module Renderer.
	virtual std::weak_ptr<Renderer> getRenderer();

private:
	
	//	The Associated Module Renderer.
	std::weak_ptr<Renderer> renderer;


};

