#pragma once

#include <vector>
#include <sstream>
#include <iostream>
#include <memory>
#include <map>
#include <algorithm>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\matrix_inverse.hpp"

#include "RenderingCommands.h"
#include "SceneMetaData.h"

#include "../Resources/ResourceData/MaterialData/MaterialData.h"
#include "../Resources/ResourceData/ShaderData/ShaderData.h"
#include "../Resources/ResourceData/TextureData/TextureData.h"

#include "../RendererResourceManagers/RendererGeometryManager/RendererGeometryManager.h"
#include "../RendererResourceManagers/RendererLightManager/RendererLightManager.h"
#include "../RendererResourceManagers/RendererMaterialManager/RendererMaterialManager.h"
#include "../RendererResourceManagers/RendererTextureManager/RendererTextureManager.h"
#include "../RendererResourceManagers/RendererShaderManager/RendererShaderManager.h"

class Configuration;
class MainResourceManager;

class Renderable;
class Transform;
class Camera;

class Renderer : public std::enable_shared_from_this<Renderer>
{
public:

	//	Default Renderer Constructor
	Renderer();

	//	Default Renderer Destructor
	virtual ~Renderer();

	//	Miscellaneous set up of the Renderer.
	virtual void initializeRenderer() = 0;

	//	Return the ID of the newly created Renderable.
	virtual long int createRenderable() = 0;

	//	The ID specifying the renderable to view.
	virtual std::shared_ptr<const Renderable> viewRenderable(const long int & renderableID) const = 0;

	//	Add Comments - TO Do
	virtual void updateShadingType(const long int & renderableID, const std::string & newShaderType) = 0;
	virtual void updateGeometryType(const long int & renderableID, const std::string & newGeometryType) = 0;
	virtual void updateMaterialType(const long int & renderableID, const std::string & newMaterialType) = 0;
	virtual void updateTransformMatrix(const long int & renderableID, const glm::mat4 & newModelMatrix) = 0;


	//	Render!
	virtual void render(const float & deltaFrameTime, const float & currentFrameTime, const float & lastFrameTime, std::shared_ptr<const Camera> camera) = 0;

	//	Remove the Renderable specified by ID.
	virtual void removeRenderable(const long int & renderableID) = 0;

	//	Miscellaneous clean up of the Renderer.
	virtual void cleanUpRenderer() = 0;

	//	Return the Scene Quality.
	virtual const SceneQuality & getSceneQuality();

	//	Add Comments - TO DO
	virtual void addMaterial(std::string newMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData);
	virtual void updateMaterial(std::string currentMaterialName, std::shared_ptr<const RendererMaterialData> newMaterialData);
	virtual void deleteMaterial(std::string deadMaterialName);

	virtual void addGeometry(std::string newGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData);
	virtual void updateGeometry(std::string currentGeometryName, std::shared_ptr<const RendererGeometryData> newGeometryData);
	virtual void deleteGeometry(std::string deadGeometryName);

	virtual void addShader(std::shared_ptr<RendererShaderData> newShaderData);
	virtual void deleteShader(std::string deadShaderName);

	virtual void addLight(std::string newLightName, std::shared_ptr<const RendererLightData> newLightData);
	virtual void updateLight(std::string currentLightName, std::shared_ptr<const RendererLightData> newLightData);
	virtual void deleteLight(std::string deadLightName);

	virtual void addTexture(std::string newTextureName, std::shared_ptr<const TextureData> newTextureData);
	virtual void updateTexture(std::string currentTextureName, std::shared_ptr<const TextureData> newTextureData);
	virtual void deleteTexture(std::string deadTextureName);

	//	Set the ShaderManager of the Renderer
	void setShaderManager(std::shared_ptr<RendererShaderManager> newShaderManager);

	//	Return the associated ShaderManager.
	std::shared_ptr<RendererShaderManager> getShaderManager();

	//	Set the TextureManager of the Renderer
	void setTextureManager(std::shared_ptr<RendererTextureManager> newTextureManager);

	//	Return the associated TextureManager.
	std::shared_ptr<RendererTextureManager> getTextureManager();

	//	Set the GeometryManager of the Renderer
	void setGeometryManager(std::shared_ptr<RendererGeometryManager> newGeometryManager);

	//	Return the associated GeometryManager.
	std::shared_ptr<RendererGeometryManager> getGeometryManager();


	//	Set the LightManager of the Renderer
	void setLightManager(std::shared_ptr<RendererLightManager> newLightManager);

	//	Return the associated LightManager.
	std::shared_ptr<RendererLightManager> getLightManager();


	//	Set the MaterialManager of the Renderer
	void setMaterialManager(std::shared_ptr<RendererMaterialManager> newMaterialManager);

	//	Return the associated MaterialManager.
	std::shared_ptr<RendererMaterialManager> getMaterialManager();


private:
	
	//	The Associated ShaderManager.
	std::shared_ptr<RendererShaderManager> rendererShaderManager;

	//	The Associated MaterialManager.
	std::shared_ptr<RendererMaterialManager> rendererMaterialManager;

	//	The Associated LightManager.
	std::shared_ptr<RendererLightManager> rendererLightManager;

	//	The Associated GeometryManager.
	std::shared_ptr<RendererGeometryManager> rendererGeometryManager;

	//	The Associated TextureManager.
	std::shared_ptr<RendererTextureManager> rendererTextureManager;

	//	The Associated Scene Quality.
	SceneQuality defaultSceneQuality;

};

