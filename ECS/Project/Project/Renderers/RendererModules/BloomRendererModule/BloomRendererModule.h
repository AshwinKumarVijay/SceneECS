#pragma once
#include <memory>

class Renderer;

class BloomRendererModule
{
public:

	//	Default Bloom Renderer Module Constructor.
	BloomRendererModule(std::shared_ptr<Renderer> newRenderer, const unsigned int & newSourceTextureID);

	//	Default Bloom Renderer Module Destructor.
	virtual ~BloomRendererModule();


private:


};

