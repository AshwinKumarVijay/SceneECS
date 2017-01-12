#include "RendererModule.h"


//	Default RendererModule Constructor.
RendererModule::RendererModule(std::shared_ptr<Renderer> newRenderer)
{
	renderer = newRenderer;
}

//	Default RendererModule Destructor.
RendererModule::~RendererModule()
{

}

//	Return the weak_ptr to the Renderer.
std::weak_ptr<Renderer> RendererModule::getRenderer()
{
	return renderer;
}
