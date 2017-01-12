#include "RendererTextureManager.h"
#include "../Resources/ResourceData/TextureData/TextureData.h"

//	Default RendererTextureManager Constructor
RendererTextureManager::RendererTextureManager()
{

}

//	Default RendererTextureManager Destructor
RendererTextureManager::~RendererTextureManager()
{

}

//	Add the Texture to the Renderer Texture Manager.
void RendererTextureManager::addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	//	Renderer Texture Data.
	std::shared_ptr<RendererTextureData> newRendererTextureData = std::make_shared<RendererTextureData>();

	//	Set the Origin to be the Lower Left of the Image. This ensures (0,0) to be the lower left pixel.
	newRendererTextureData->textureType = newTextureData->getTextureType();
	newRendererTextureData->textureWidth = newTextureData->viewTextureBufferData(0)->getWidth();
	newRendererTextureData->textureHeight = newTextureData->viewTextureBufferData(0)->getHeight();

	//	
	if (newRendererTextureData->textureType == GL_TEXTURE_2D)
	{
		//	Generate the New Texture.
		glGenTextures(1, &newRendererTextureData->textureID);

		//	Bind it to the appropriate location.
		glBindTexture(GL_TEXTURE_2D, newRendererTextureData->textureID);

		//
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//	Set the Texture parameters.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newTextureData->viewTextureBufferData(0)->getWidth(), newTextureData->viewTextureBufferData(0)->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, newTextureData->viewTextureBufferData(0)->viewTextureBufferData());

		//	Bind it to the appropriate location.
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	else if (newRendererTextureData->textureType == GL_TEXTURE_CUBE_MAP)
	{
		//	Generate the New Texture.
		glGenTextures(1, &newRendererTextureData->textureID);

		//	Bind it to the appropriate location.
		glBindTexture(GL_TEXTURE_CUBE_MAP, newRendererTextureData->textureID);

		//	
		for (int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, newTextureData->viewTextureBufferData(i)->getWidth(), newTextureData->viewTextureBufferData(i)->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, newTextureData->viewTextureBufferData(i)->viewTextureBufferData());
		}

		//
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	//	
 	mapNameToTextureData[newTextureName] = newRendererTextureData;
}


//	Update the Texture.
void RendererTextureManager::updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	//	Find the Texture Data associated with the requested texture name.
	auto itr = mapNameToTextureData.find(currentTextureName);

	//	Check if there is actually any texture data associated wtih the texture name.
	if (itr != mapNameToTextureData.end())
	{
		//	Bind it to the appropriate location.
		glBindTexture(GL_TEXTURE_2D, itr->second->textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newTextureData->viewTextureBufferData(0)->getWidth(), newTextureData->viewTextureBufferData(0)->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, newTextureData->viewTextureBufferData(0)->viewTextureBufferData());
		//	Bind it to the appropriate location.
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		//	Throw error texture not found.
	}
}

//	Return a pointer to the RendererTextureData.
std::shared_ptr<const RendererTextureData> RendererTextureManager::viewTexture(std::string requestedTextureName) const
{
	//	Find the Texture Data associated with the requested texture name.
	auto itr = mapNameToTextureData.find(requestedTextureName);

	//	Check if there is actually any texture data associated wtih the texture name.
	if (itr != mapNameToTextureData.end())
	{
		//	Returh the Data.
		return itr->second;
	}
	else
	{
		//	Return NULL if there is no texture data.
		return NULL;
	}
}

//	Delete the Texture.
void RendererTextureManager::deleteTexture(std::string deadTextureName)
{
	//	Find the Texture Data associated with the texture name.
	auto itr = mapNameToTextureData.find(deadTextureName);

	//	Check if there is actually any texture data associated wtih the texture name.
	if (itr != mapNameToTextureData.end())
	{

	}
	else
	{
		//	Throw error texture not found.
	}
}
