#pragma once
#include "../../../../TextureGeneratorSelector/TextureGeneratorSelector.h"

class SceneTextureResource
{

public:

	//	Default SceneTextureResource Constructor.
	SceneTextureResource();

	//	Default SceneTextureResource Destructor.
	virtual ~SceneTextureResource();


private:

	//	The Image Height, and the Image Width.
	unsigned int imageHeight, imageWidth;	

	//	The Image Data.
	unsigned char * pixelData;

	//	The Internal Image Format.
	unsigned int imageInternalFormat, imageFormat;
};

