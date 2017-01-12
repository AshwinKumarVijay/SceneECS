#pragma once

#include "../ECS/System/System.h"


class Component;
class HierarchyComponent;
class TransformComponent;
class PhysicsComponent;
class GeometryComponent;
class MaterialComponent;
class RenderingComponent;
class CameraComponent;
class LightComponent;

class Renderer;
class ModuleRenderer;

class Camera;

class MaterialData;
class TextureData;
class GeometryData;
class ShaderData;

class RenderingSystem : public System
{

public:

	//	Default Rendering System Constructor. The Entity Manager and the Event Queue the System will use.
	RenderingSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);
	
	//	Default Rendering System Destructor.
	virtual ~RenderingSystem();

	//	Miscellaneous initialization of the System.
	virtual void initializeSystem();

	//	Update the System - Render!
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);
	
	//	Return a pointer to the Renderer.
	std::shared_ptr<Renderer> getRenderer();

	//	Shut Down the System.
	virtual void shutDownSystem();

	//	Destroy the System.
	virtual void destroySystem();



protected:

	//	Process the Events that have occurred.
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

private:

	//	Process the Resource Events.
	virtual void processResourceEvents(std::shared_ptr<const ECSEvent> nextEvent);

	//	Add a renderable to the renderer.
	virtual void addRenderable(const long int & entityID);

	//	Update the Renderable associated with the entity specified by Entity ID.
	virtual void updateRenderable(const long int & entityID);

	//	Remove the Renderable associated with the entity specified by Entity ID.
	virtual void removeRenderable(const long int & entityID);


	//	Update the Camera.
	virtual void updateCamera();

	//	Update the Shader Type of the Renderable associated with the entity specified by Entity ID.
	virtual void updateRenderableShaderType(const long int & entityID);

	//	Update the Material Type of the Renderable associated with the entity specified by Entity ID.
	virtual void updateRenderableMaterialType(const long int & entityID);

	//	Update the Geometry Type of the Renderable associated with the entity specified by Entity ID.
	virtual void updateRenderableGeometryType(const long int & entityID);

	//	Update the Transform Matrix of the Renderable associated with the entity specified by Entity ID.
	virtual void updateRenderableTransformMatrix(const long int & entityID);


	//	Create the Light.
	virtual void createLight(const long int & entityID);

	//	Update the Light.
	virtual void updateLight(const long int & entityID);

	//	Delete the Light.
	virtual void deleteLight(const long int & entityID);
	
	//	Create the Geometry.
	virtual void createGeometry(const std::string & newGeometryName, std::shared_ptr<const GeometryData> newGeometryData);

	//	Update the Geometry.
	virtual void updateGeometry(const std::string & currentGeometryName, std::shared_ptr<const GeometryData> updatedGeometryData);

	//	Delete the Geometry.
	virtual void deleteGeometry(const std::string & deadGeometryName);


	//	Create the Material.
	virtual void createMaterial(const std::string & newMaterialName, std::shared_ptr<const MaterialData> newMaterialData);

	//	Update the Material.
	virtual void updateMaterial(const std::string & currentMaterialName, std::shared_ptr<const MaterialData> updatedMaterialData);

	//	Delete the Material.
	virtual void deleteMaterial(const std::string & deadMaterialName);


	//	Create the Shader.
	virtual void createShader(std::shared_ptr<const ShaderData> newShaderData);

	//	Update the Shader.
	virtual void updateShader(std::shared_ptr<const ShaderData> updatedShaderData);

	//	Delete the Shader.
	virtual void deleteShader(const std::string & deadShaderName);


	//	Create the Texture.
	virtual void createTexture(const std::string & newTextureName, std::shared_ptr<const TextureData> newTextureData);

	//	Update the Texture.
	virtual void updateTexture(const std::string & currentTextureName, std::shared_ptr<const TextureData> updatedTextureData);
	
	//	Delete the Texture.
	virtual void deleteTexture(const std::string & deadTextureName);



	//	A pointer to the associated Renderer.
	std::shared_ptr<Renderer> renderer;

	//	A pointer to the default camera.
	std::shared_ptr<Camera> defaultCamera;

	//	A pointer to the active camera.
	std::shared_ptr<Camera> activeCamera;
};

