#include "Renderer.h"

#include "../Transform/Transform.h"
#include "../Renderable/Renderable.h"
#include "../Camera/Camera.h"

//	Default Renderer Constructor
Renderer::Renderer()
{
	rendererMaterialManager = std::make_shared<RendererMaterialManager>();
	rendererShaderManager = std::make_shared<RendererShaderManager>();
	rendererTextureManager = std::make_shared<RendererTextureManager>();
	rendererLightManager = std::make_shared<RendererLightManager>();
	rendererGeometryManager = std::make_shared<RendererGeometryManager>();

	//	Screen Width and Screen Height.
	defaultSceneQuality.screenWidth = 1600;
	defaultSceneQuality.screenHeight = 900;

	//	Scene Quality - Bloom Blur.
	defaultSceneQuality.bloomBlur = 1;
	defaultSceneQuality.bloomThreshold = 1;

	//	Scene Quality - SSAO.
	defaultSceneQuality.ssaoQuality = 4;

	//	Scene Quality - Shadow Resolution.
	defaultSceneQuality.shadowSize = 2048;
}

//	Default Renderer Destructor
Renderer::~Renderer()
{

}

//	Set the MaterialManager of the Renderer.
void Renderer::setMaterialManager(std::shared_ptr<RendererMaterialManager> newMaterialManager)
{
	rendererMaterialManager = newMaterialManager;
}

//	Return the MaterialManager of the Renderer.
std::shared_ptr<RendererMaterialManager> Renderer::getMaterialManager()
{
	return rendererMaterialManager;
}

//	Set the ShaderManager of the Renderer.
void Renderer::setShaderManager(std::shared_ptr<RendererShaderManager> newShaderManager)
{
	rendererShaderManager = newShaderManager;
}

//	Return the ShaderManager of the Renderer.
std::shared_ptr<RendererShaderManager> Renderer::getShaderManager()
{
	return rendererShaderManager;
}

//	Set the TextureManager of the Renderer.
void Renderer::setTextureManager(std::shared_ptr<RendererTextureManager> newTextureManager)
{
	rendererTextureManager = newTextureManager;
}

//	Return the TextureManager of the Renderer.
std::shared_ptr<RendererTextureManager> Renderer::getTextureManager()
{
	return rendererTextureManager;
}

//	Set the GeometryManager of the Renderer.
void Renderer::setGeometryManager(std::shared_ptr<RendererGeometryManager> newGeometryManager)
{
	rendererGeometryManager = newGeometryManager;
}

//	Return the Geometry Manager of the Renderer.
std::shared_ptr<RendererGeometryManager> Renderer::getGeometryManager()
{
	return rendererGeometryManager;
}

//	Set the LightManager of the Renderer.
void Renderer::setLightManager(std::shared_ptr<RendererLightManager> newLightManager)
{
	rendererLightManager = newLightManager;
}

//	Return the LightManager of the Renderer.
std::shared_ptr<RendererLightManager> Renderer::getLightManager()
{
	return rendererLightManager;
}

//	Return the Scene Quality.
const SceneQuality & Renderer::getSceneQuality()
{
	return defaultSceneQuality;
}


//	Add a Material to use in the Renderer.
void Renderer::addMaterial(std::string newMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData)
{
	rendererMaterialManager->addMaterial(newMaterialName, newMaterialData);
}

//	Update the existing Material in the Renderer.
void Renderer::updateMaterial(std::string currentMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData)
{
	rendererMaterialManager->updateMaterial(currentMaterialName, newMaterialData);
}

//	Delete the Material in the Renderer.
void Renderer::deleteMaterial(std::string deadMaterialName)
{
	rendererMaterialManager->deleteMaterial(deadMaterialName);
}

//	Add a new Geometry to use in the Renderer.
void Renderer::addGeometry(std::string newGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData)
{
	rendererGeometryManager->addGeometry(newGeometryName, newGeometryData);
}

//	update the new Geometry to use in the Renderer.
void Renderer::updateGeometry(std::string currentGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData)
{
	rendererGeometryManager->updateGeometry(currentGeometryName, newGeometryData);
}

//	Delete the Geometry in the Renderer.
void Renderer::deleteGeometry(std::string deadGeometryName)
{
	rendererGeometryManager->deleteGeometry(deadGeometryName);
}

//	Add a Shader to use in the Renderer.
void Renderer::addShader(std::shared_ptr<RendererShaderData> newShaderData)
{
	rendererShaderManager->addShader(newShaderData);
}

//	Delete the Shader.
void Renderer::deleteShader(std::string deadShaderName)
{
	rendererShaderManager->deleteShader(deadShaderName);
}

//	Add the Light.
void Renderer::addLight(std::string newLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	rendererLightManager->addLight(newLightName, newLightData);
}

//	Update the Light.
void Renderer::updateLight(std::string currentLightName, std::shared_ptr<const RendererLightData> newLightData)
{
	rendererLightManager->updateLight(currentLightName, newLightData);
}

//	Delete the Light.
void Renderer::deleteLight(std::string deadLightName)
{
	rendererLightManager->deleteLight(deadLightName);
}

//	Add the Texture.
void Renderer::addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	rendererTextureManager->addTexture(newTextureName, newTextureData);
}

//	Uodate the Texture.
void Renderer::updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	rendererTextureManager->updateTexture(currentTextureName, newTextureData);
}

//	Delete the Texture.
void Renderer::deleteTexture(std::string deadTextureName)
{
	rendererTextureManager->deleteTexture(deadTextureName);
}
