#include "RenderingSystem.h"

#include "../../ECS/EntityManager/EntityManager.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../../ECS/ECSEvent/ECSEvent.h"
#include "../Events/ResourceEvent/ResourceEvent.h"

#include "../Renderers/Renderer/Renderer.h"
#include "../Renderers/ModuleRenderer/ModuleRenderer.h"

#include "../Renderers/Renderable/Renderable.h"

#include "../Camera/Camera.h"

#include "../../ECS/Component/Component.h"
#include "../Components/HierarchyComponent/HierarchyComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../Components/GeometryComponent/GeometryComponent.h"
#include "../Components/RenderingComponent/RenderingComponent.h"
#include "../Components/CameraComponent/CameraComponent.h"
#include "../Components/LightComponent/LightComponent.h"

#include "../../Resources/ResourceData/GeometryData/GeometryData.h"

#include "../../Renderers/RendererResourceManagers/RendererShaderManager/RendererShaderData/RendererShaderData.h"

#include "../Transform/Transform.h"

//	Default RenderingSystem Constructor
RenderingSystem::RenderingSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	:System(newEntityManager, newEventQueue, "TRANSFORM_SYSTEM")

{

}

//	Default RenderingSystem Destructor
RenderingSystem::~RenderingSystem()
{

}

//	Initialize the Rendering System.
void RenderingSystem::initializeSystem()
{
	//	Create the Default Renderer.
	renderer = std::make_shared<ModuleRenderer>();

	//	Initialize the Renderer.
	renderer->initializeRenderer();

	//	Create a Default Camera, which will have the default camera data.
	defaultCamera = std::make_shared<Camera>();

	//	Create an Active Camera, into which we will copy over the data camera data, and use it for rendering.
	activeCamera = std::make_shared<Camera>();
}

//	Update the Rendering System this frame.
void RenderingSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Process the Events.
	processEvents(deltaTime, currentFrameTime, lastFrameTime);

	//	Update the Active Camera.
	activeCamera->updateCamera();

	//	Render the Renderer
	renderer->render(deltaTime, currentFrameTime, lastFrameTime, activeCamera);
}

//	Process the Events that have occurred.
void RenderingSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Check if there are any Events.
	while (getReceiver()->getNumberOfEvents() > 0)
	{
		//	Get the events.
		std::shared_ptr<const ECSEvent> nextEvent = getReceiver()->getNextEvent();

		//	Make sure this Event was not sent out by the Rendering System.
		if (nextEvent->getModuleOrigin() != "RENDERING_SYSTEM")
		{
			//	Component Added.
			if (nextEvent->getEventType() == EventType::COMPONENT_ADDED)
			{
				//	Check if the component added was a Rendering Component.
				if (nextEvent->getComponentType() == ComponentType::RENDERING_COMPONENT)
				{
					addRenderable(nextEvent->getEntityID());
				}
				else if(nextEvent->getComponentType() == ComponentType::LIGHT_COMPONENT)
				{
					createLight(nextEvent->getEntityID());
				}

			}	//	Component Changed.
			else if (nextEvent->getEventType() == EventType::COMPONENT_CHANGED)
			{
				//	Check if the component changed was the Transform Component.
				if (nextEvent->getComponentType() == ComponentType::TRANSFORM_COMPONENT)
				{
					updateRenderable(nextEvent->getEntityID());
					updateLight(nextEvent->getEntityID());
					updateCamera();

				}	//	Check if the component changed was the Geometry Component.
				else if (nextEvent->getComponentType() == ComponentType::GEOMETRY_COMPONENT)
				{
					updateRenderable(nextEvent->getEntityID());

				}	//	Check if the component changed was the Rendering Component.
				else if (nextEvent->getComponentType() == ComponentType::RENDERING_COMPONENT)
				{
					updateRenderable(nextEvent->getEntityID());

				}	//	Check if the component changed was the Camera Component.
				else if (nextEvent->getComponentType() == ComponentType::CAMERA_COMPONENT)
				{
					updateCamera();
				}
				else if(nextEvent->getComponentType() == ComponentType::LIGHT_COMPONENT)
				{
					updateLight(nextEvent->getEntityID());
				}
				else
				{

				}

			}	//	Component Destroyed.
			else if (nextEvent->getEventType() == EventType::COMPONENT_DESTROYED)
			{
				//	Check if the component changed destroyed was a Rendering Component.
				if (nextEvent->getComponentType() == ComponentType::RENDERING_COMPONENT)
				{
					removeRenderable(nextEvent->getEntityID());
				}
				else if (nextEvent->getComponentType() == ComponentType::CAMERA_COMPONENT)
				{
					updateCamera();
				}
				else if (nextEvent->getComponentType() == ComponentType::LIGHT_COMPONENT)
				{
					deleteLight(nextEvent->getEntityID());
				}

			}	//	Shut Down the System.
			else if (nextEvent->getEventType() == EventType::ECS_SHUTDOWN_EVENT)
			{
				shutDownSystem();
			}
		}

		//	Process the Resource Events.
		processResourceEvents(nextEvent);
	}
}

//	Process the Event if it is a ResourceEvent.
void RenderingSystem::processResourceEvents(std::shared_ptr<const ECSEvent> nextEvent)
{
	//	Convert the event to a Resource ECS Event.
	std::shared_ptr<const ResourceEvent> resourceEvent = std::dynamic_pointer_cast<const ResourceEvent>(nextEvent);

	//	Check if it was a Resource ECS Event.
	if (resourceEvent != NULL)
	{
		if (resourceEvent->getEventType() == EventType::RESOURCE_EVENT)
		{
			if (resourceEvent->getResourceEventType() == ResourceEventType::RESOURCE_ADDED)
			{
				//	Add the Geometry resource, if the event was a Geometry resource event.
				if (resourceEvent->getResourceType() == ResourceType::GEOMETRY_RESOURCE)
				{					
					createGeometry(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const GeometryData>(resourceEvent->getResourceData()));

				}	//	Add the Material resource, if the event was a Material resource event.
				else if (resourceEvent->getResourceType() == ResourceType::MATERIAL_RESOURCE)
				{
					createMaterial(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const MaterialData>(resourceEvent->getResourceData()));

				}	//	Add the Shader resource, if the event was a Shader resource event.
				else if (resourceEvent->getResourceType() == ResourceType::SHADER_RESOURCE)
				{
					createShader(std::dynamic_pointer_cast<const ShaderData>(resourceEvent->getResourceData()));

				}	//	Add the Texture resource, if the event was a Texture resource event.
				else if (resourceEvent->getResourceType() == ResourceType::TEXTURE_RESOURCE)
				{
					createTexture(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const TextureData>(resourceEvent->getResourceData()));
				}
			}
			else if (resourceEvent->getResourceEventType() == ResourceEventType::RESOURCE_UPDATED)
			{
				//	Add the Geometry resource, if the event was a Geometry resource event.
				if (resourceEvent->getResourceType() == ResourceType::GEOMETRY_RESOURCE)
				{
					updateGeometry(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const GeometryData>(resourceEvent->getResourceData()));
				}	//	Add the Material resource, if the event was a Material resource event.
				else if (resourceEvent->getResourceType() == ResourceType::MATERIAL_RESOURCE)
				{
					updateMaterial(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const MaterialData>(resourceEvent->getResourceData()));
				}	//	Add the Texture resource, if the event was a Texture resource event.
				else if (resourceEvent->getResourceType() == ResourceType::TEXTURE_RESOURCE)
				{
					updateTexture(resourceEvent->getResourceName(), std::dynamic_pointer_cast<const TextureData>(resourceEvent->getResourceData()));
				}
			}
			else if (resourceEvent->getResourceEventType() == ResourceEventType::RESOURCE_DESTROYED)
			{
				//	Delete the appropriate Geometry resource, if it is a Geometry resource.
				if (resourceEvent->getResourceType() == ResourceType::GEOMETRY_RESOURCE)
				{
					deleteGeometry(resourceEvent->getResourceName());
				}	//	Delete the appropriate Material resource, if it is a Material resource.
				else if (resourceEvent->getResourceType() == ResourceType::MATERIAL_RESOURCE)
				{
					deleteMaterial(resourceEvent->getResourceName());
				}	//	Delete the appropriate Shader resource, if it is a Shader resource.
				else if (resourceEvent->getResourceType() == ResourceType::SHADER_RESOURCE)
				{
					deleteShader(resourceEvent->getResourceName());
				}	//	Dlete the appropriate Texture resource, if it is a Texture resource.
				else if (resourceEvent->getResourceType() == ResourceType::TEXTURE_RESOURCE)
				{
					deleteTexture(resourceEvent->getResourceName());
				}
			}
		}
	}
}

//	Return a pointer to the Renderer associated with the Renderer.
std::shared_ptr<Renderer> RenderingSystem::getRenderer()
{
	return renderer;
}
	
//	Shut Down the System.
void RenderingSystem::shutDownSystem()
{
	renderer->cleanUpRenderer();
}

//	Clean up the Rendering System.
void RenderingSystem::destroySystem()
{

}

//	Add the Renderable to the associated Renderer.
void RenderingSystem::addRenderable(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<RenderingComponent> renderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT, "RENDERING_SYSTEM"));
	
	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getActiveRendering() && renderingComponent->getRenderableID() == -1)
	{
		//	Get the Transform Component of the current entity.
		std::shared_ptr<const TransformComponent> transformComponent = std::dynamic_pointer_cast<const TransformComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::TRANSFORM_COMPONENT));

		//	Get the Geometry Component of the current entity.
		std::shared_ptr<const GeometryComponent> geometryComponent = std::dynamic_pointer_cast<const GeometryComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::GEOMETRY_COMPONENT));

		//	Set the RenderableID associated with the RenderingComponent.
		renderingComponent->setRenderableID(renderer->createRenderable());

		//	Update the Shader Type associated with the Renderable of this EntityID.
		updateRenderableShaderType(entityID);

		//	Update the Geometry Type associated with the Renderable of this EntityID.
		updateRenderableGeometryType(entityID);

		//	Update the Material Type associated with the Renderable of this EntityID.
		updateRenderableMaterialType(entityID);

		//	Update the Transform associated with the Renderable of this EntityID.
		updateRenderableTransformMatrix(entityID);
	}
}

//	Update the Renderable.
void RenderingSystem::updateRenderable(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<const RenderingComponent> renderingComponent = std::dynamic_pointer_cast<const RenderingComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT));

	//	Check if this Rendering Component is Active Rendering.
	if (renderingComponent != NULL && !renderingComponent->getActiveRendering())
	{
		if (renderingComponent->getRenderableID() != -1)
		{
			//	
			std::shared_ptr<RenderingComponent> currentRenderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT, "RENDERING_SYSTEM"));
			
			//	
			removeRenderable(currentRenderingComponent->getRenderableID());

			//	
			currentRenderingComponent->setRenderableID(-1);

		}
	}	
	else if(renderingComponent != NULL && renderingComponent->getActiveRendering())
	{
		if (renderingComponent->getRenderableID() == -1)
		{
			addRenderable(entityID);
		}

		//	Update the Shader Type associated with the Renderable of this EntityID.
		updateRenderableShaderType(entityID);

		//	Update the Material Type associated with the Renderable of this EntityID.
		updateRenderableMaterialType(entityID);

		//	Update the Geometry Type associated with the Renderable of this EntityID.
		updateRenderableGeometryType(entityID);

		//	Update the Transform Matrix associated with the Renderable of this EntityID.
		updateRenderableTransformMatrix(entityID);
	}
	else
	{

	}
}





//	Remove the Renderable.
void RenderingSystem::removeRenderable(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<RenderingComponent> renderingComponent = std::dynamic_pointer_cast<RenderingComponent>(getEntityManager()->getComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT, "RENDERING_SYSTEM"));

	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() != -1)
	{
		//	Remove the Renderable from the Renderer.
		renderer->removeRenderable(entityID);

		//	Set the Renderable ID.
		renderingComponent->setRenderableID(-1);
	}
}


//	Update the Camera used with Renderer.
void RenderingSystem::updateCamera()
{
	//	Get the EntityManager.
	std::shared_ptr<EntityManager> entityManager = getEntityManager();

	//	Get the entities with a Transform Component.
	std::shared_ptr<std::vector<long int>> entities = entityManager->getEntitiesWithComponentOfType(ComponentType::CAMERA_COMPONENT);

	//	Check if an Active Camera Component was found.
	bool activeCameraAvailable = false;

	//	If there are no entities, we do not really have to do anything.
	if (entities != NULL)
	{
		//	Iterate over the entities, and process them.
		for (auto currentEntity : *entities)
		{

			//	Get the Camera Component.
			std::shared_ptr<const TransformComponent> transformComponent = std::dynamic_pointer_cast<const TransformComponent>(entityManager->viewComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT));

			//	Get the Camera Component.
			std::shared_ptr<const CameraComponent> cameraComponent = std::dynamic_pointer_cast<const CameraComponent>(entityManager->viewComponentOfEntity(currentEntity, ComponentType::CAMERA_COMPONENT));

			//	Check if this is the Actice Camera.
			if (cameraComponent->getIsActive())
			{
				//	Active Camera.
				activeCameraAvailable = true;

				//	Set the Transform Related Camera Properties.
				activeCamera->setCameraPosition(transformComponent->viewTransform()->getPosition());
				activeCamera->setUpVector(transformComponent->viewTransform()->getUpVector());
				activeCamera->setLookAtDirection(transformComponent->viewTransform()->getFowardDirection());

				//	Set the Aspect Ratio and Field of View.
				activeCamera->setAspectRatio(cameraComponent->getAspectRatio());
				activeCamera->setFOV(cameraComponent->getFOV());

				//	Set the Near and Far Clip.
				activeCamera->setFarClip(cameraComponent->getFarClip());
				activeCamera->setNearClip(cameraComponent->getNearClip());

			}
		}
	}

	//	If an Active Camera Component was not found, use the default camera properties.
	if (activeCameraAvailable == false)
	{
		//	Set the Transform Related Camera Properties.
		activeCamera->setCameraPosition(defaultCamera->getCameraPosition());
		activeCamera->setUpVector(defaultCamera->getUpVector());
		activeCamera->setLookAtDirection(defaultCamera->getLookAtDirection());

		//	Set the Aspect Ratio and Field of View.
		activeCamera->setAspectRatio(defaultCamera->getAspectRatio());
		activeCamera->setFOV(defaultCamera->getFOV());

		//	Set the Near and Far Clip.
		activeCamera->setFarClip(defaultCamera->getFarClip());
		activeCamera->setNearClip(defaultCamera->getNearClip());
	}
}



//	Update the Shader Type of the specified Renderable.
void RenderingSystem::updateRenderableShaderType(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<const RenderingComponent> renderingComponent = std::dynamic_pointer_cast<const RenderingComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT));

	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() != -1)
	{
		//	Update the Shader Type associated with this Renderable.
		renderer->updateShadingType(renderingComponent->getRenderableID(), renderingComponent->getShadingType());
	}
}

//	Update the Material Type of the specified Renderable.
void RenderingSystem::updateRenderableMaterialType(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<const RenderingComponent> renderingComponent = std::dynamic_pointer_cast<const RenderingComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT));

	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() != -1)
	{
		//	Update the Material Name associated with this Renderable.
		renderer->updateMaterialType(renderingComponent->getRenderableID(), renderingComponent->getMaterialType());
	}
}

//	Update the Geometry Type of the specified Renderable.
void RenderingSystem::updateRenderableGeometryType(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<const RenderingComponent> renderingComponent = std::dynamic_pointer_cast<const RenderingComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT));

	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() != -1)
	{
		//	Get the Geometry Component of the current entity.
		std::shared_ptr<const GeometryComponent> geometryComponent = std::dynamic_pointer_cast<const GeometryComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::GEOMETRY_COMPONENT));

		//	Update the Geometry Name associated with this Renderable.
		renderer->updateGeometryType(renderingComponent->getRenderableID(), geometryComponent->getGeometryType());

	}
}

//	Update the Transform Matrix of the specified Renderable.
void RenderingSystem::updateRenderableTransformMatrix(const long int & entityID)
{
	//	Get the Rendering Component of the current entity.
	std::shared_ptr<const RenderingComponent> renderingComponent = std::dynamic_pointer_cast<const RenderingComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT));

	//	Check if there is actual Rendering Component.
	if (renderingComponent != NULL && renderingComponent->getRenderableID() != -1)
	{
		//	Get the Transform Component of the current entity.
		std::shared_ptr<const TransformComponent> transformComponent = std::dynamic_pointer_cast<const TransformComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::TRANSFORM_COMPONENT));

		//	Update the Transform associated with this Renderable.
		renderer->updateTransformMatrix(renderingComponent->getRenderableID(), *transformComponent->viewTransform()->getHierarchyTransformMatrix());
	}
}

void RenderingSystem::createLight(const long int & entityID)
{
	//	Get the Transform and Light Components of the current entity.
	std::shared_ptr<const TransformComponent> transformComponent = std::dynamic_pointer_cast<const TransformComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::TRANSFORM_COMPONENT));
	std::shared_ptr<const LightComponent> lightComponent = std::dynamic_pointer_cast<const LightComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::LIGHT_COMPONENT));

	if (transformComponent != NULL && lightComponent != NULL )
	{
		std::shared_ptr<RendererLightData> newLightData = std::make_shared<RendererLightData>();

		newLightData->lightEnabledShadowLightType = glm::vec4(1.0, 1.0, 1.0, 0.0);
		newLightData->lightPosition = (*(transformComponent->viewTransform()->getHierarchyTransformMatrix())) * glm::vec4(0.0, 00.0, 00.0, 1.0);
		newLightData->lightColorAndLightIntensity = glm::vec4(1.0, 1.0, 1.0, 1.0);
		newLightData->lightConeDirection = glm::vec4(0.0, 0.0, 0.0, 0.0);
		newLightData->lightDistanceAttenuation = glm::vec4(0.0, 0.0, 0.0, 0.0);


		renderer->addLight(std::to_string(entityID), newLightData);
	}
}

void RenderingSystem::updateLight(const long int & entityID)
{
	//	Get the Transform and Light Components of the current entity.
	std::shared_ptr<const TransformComponent> transformComponent = std::dynamic_pointer_cast<const TransformComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::TRANSFORM_COMPONENT));
	std::shared_ptr<const LightComponent> lightComponent = std::dynamic_pointer_cast<const LightComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::LIGHT_COMPONENT));

	if (transformComponent != NULL && lightComponent != NULL)
	{
		std::shared_ptr<RendererLightData> newLightData = std::make_shared<RendererLightData>();

		//	renderer->updateLight(std::to_string(entityID), newLightData);
	}

}

void RenderingSystem::deleteLight(const long int & entityID)
{
	//	Get the Transform and Light Components of the current entity.
	std::shared_ptr<const TransformComponent> transformComponent = std::dynamic_pointer_cast<const TransformComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::TRANSFORM_COMPONENT));
	std::shared_ptr<const LightComponent> lightComponent = std::dynamic_pointer_cast<const LightComponent>(getEntityManager()->viewComponentOfEntity(entityID, ComponentType::LIGHT_COMPONENT));

	if (transformComponent != NULL && lightComponent != NULL)
	{
		//	Delete the Light associated with the Entity.
		renderer->deleteLight(std::to_string(entityID));
	}
}

//	Create the Geometry.
void RenderingSystem::createGeometry(const std::string & newGeometryName, std::shared_ptr<const GeometryData> newGeometryData)
{
	//	Create the RendererGeometryData.
	std::shared_ptr<RendererGeometryData> newRendererGeometryData = std::make_shared<RendererGeometryData>();

	newRendererGeometryData->geometryType = newGeometryName;

	newRendererGeometryData->geometryDescriptionRepresentation = newGeometryData->getGeometryDescriptionRepresentation();
	newRendererGeometryData->geometryDrawType = newGeometryData->getGeometryDrawType();

	newRendererGeometryData->indicesArray = newGeometryData->viewGeometryIndices();
	newRendererGeometryData->verticesArray = newGeometryData->viewGeometryVertices();

	newRendererGeometryData->verticesNormalData = newGeometryData->viewGeometryNormalData();
	newRendererGeometryData->verticesTextureData = newGeometryData->viewGeometryTextureData();

	//	Add the Geometry.
	renderer->addGeometry(newGeometryName, newRendererGeometryData);
}

//	Update the Geometry.
void RenderingSystem::updateGeometry(const std::string & currentGeometryName, std::shared_ptr<const GeometryData> updatedGeometryData)
{
	std::shared_ptr<RendererGeometryData> updatedRendererGeometryData = std::make_shared<RendererGeometryData>();

	updatedRendererGeometryData->geometryType = currentGeometryName;

	updatedRendererGeometryData->geometryDescriptionRepresentation = updatedGeometryData->getGeometryDescriptionRepresentation();
	updatedRendererGeometryData->geometryDrawType = updatedGeometryData->getGeometryDrawType();

	updatedRendererGeometryData->indicesArray = updatedGeometryData->viewGeometryIndices();
	updatedRendererGeometryData->verticesArray = updatedGeometryData->viewGeometryVertices();

	updatedRendererGeometryData->verticesNormalData = updatedGeometryData->viewGeometryNormalData();
	updatedRendererGeometryData->verticesTextureData = updatedGeometryData->viewGeometryTextureData();

	//	Update the Geometry.
	renderer->updateGeometry(currentGeometryName, updatedRendererGeometryData);
}

//	Delete the Geometry.
void RenderingSystem::deleteGeometry(const std::string & deadGeometryName)
{
	renderer->deleteGeometry(deadGeometryName);
}

//	Create the Material.
void RenderingSystem::createMaterial(const std::string & newMaterialName, std::shared_ptr<const MaterialData> newMaterialData)
{
	std::shared_ptr<RendererMaterialData> newRendererMaterialData = std::make_shared<RendererMaterialData>();

	newRendererMaterialData->diffuseAlbedo = newMaterialData->diffuseAlbdeo;
	newRendererMaterialData->specularAlbedo = newMaterialData->specularAlbedo;
	newRendererMaterialData->emissiveColor = newMaterialData->emissiveColor;
	newRendererMaterialData->metallicRoughnessFresnelOpacity = newMaterialData->metallicRoughnessFresnelOpacity;

	newRendererMaterialData->diffuseAlbedoMap = newMaterialData->DiffuseAlbedoMap;
	newRendererMaterialData->specularAlbedoMap = newMaterialData->SpecularAlbedoMap;
	newRendererMaterialData->normalMap = newMaterialData->NormalMap;
	newRendererMaterialData->occlusionMap = newMaterialData->OcclusionMap;

	renderer->addMaterial(newMaterialName, newRendererMaterialData);
}

//	Update the Material.
void RenderingSystem::updateMaterial(const std::string & currentMaterialName, std::shared_ptr<const MaterialData> updatedMaterialData)
{
	std::shared_ptr<RendererMaterialData> updatedRendererMaterialData = std::make_shared<RendererMaterialData>();

	updatedRendererMaterialData->diffuseAlbedo = updatedMaterialData->diffuseAlbdeo;
	updatedRendererMaterialData->specularAlbedo = updatedMaterialData->specularAlbedo;
	updatedRendererMaterialData->emissiveColor = updatedMaterialData->emissiveColor;
	updatedRendererMaterialData->metallicRoughnessFresnelOpacity = updatedMaterialData->metallicRoughnessFresnelOpacity;

	updatedRendererMaterialData->diffuseAlbedoMap = updatedMaterialData->DiffuseAlbedoMap;
	updatedRendererMaterialData->specularAlbedoMap = updatedMaterialData->SpecularAlbedoMap;
	updatedRendererMaterialData->normalMap = updatedMaterialData->NormalMap;
	updatedRendererMaterialData->occlusionMap = updatedMaterialData->OcclusionMap;

	renderer->updateMaterial(currentMaterialName, updatedRendererMaterialData);
}

//	Delete the Material.
void RenderingSystem::deleteMaterial(const std::string & deadMaterialName)
{
	renderer->deleteMaterial(deadMaterialName);
}

//	Create the Shader.
void RenderingSystem::createShader(std::shared_ptr<const ShaderData> newShaderData)
{

	//	std::shared_ptr<RendererShaderData> newRendererShaderData = std::make_shared<RendererShaderData>();
	//	renderer->addShader(newRendererShaderData);
}

//	Update the Shader.
void RenderingSystem::updateShader(std::shared_ptr<const ShaderData> updatedShaderData)
{

}

//	Delete the Shader.
void RenderingSystem::deleteShader(const std::string & deadShaderName)
{
	//	renderer->deleteShader(deadShaderName);
}

//	Create the Texture.
void RenderingSystem::createTexture(const std::string & newTextureName, std::shared_ptr<const TextureData> newTextureData)
{
	renderer->addTexture(newTextureName, newTextureData);
}

//	Update the Texture.
void RenderingSystem::updateTexture(const std::string & currentTextureName, std::shared_ptr<const TextureData> updatedTextureData)
{
	renderer->updateTexture(currentTextureName, updatedTextureData);
}

//	Delete the Texture.
void RenderingSystem::deleteTexture(const std::string & deadTextureName)
{
	renderer->deleteTexture(deadTextureName);
}
