#include "SceneECS.h"

#include "../ECS/EventQueue/EventQueue.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../ECS/EntityManager/EntityManager.h"


#include "../ECS/System/System.h"
#include "../Systems/TransformSystem/TransformSystem.h"
#include "../Systems/RenderingSystem/RenderingSystem.h"
#include "../Systems/CameraSystem/CameraSystem.h"
#include "../Systems/InputSystem/InputSystem.h"
#include "../Systems/InteractionMovementResponseSystem/InteractionMovementResponseSystem.h"

#include "../Components/HierarchyComponent/HierarchyComponent.h"
#include "../Components/GeometryComponent/GeometryComponent.h"
#include "../Components/RenderingComponent/RenderingComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../Components/LightComponent/LightComponent.h"

#include "../Transform/Transform.h"

#include "../GeometryGeneratorSelector/GeometryGeneratorSelector.h"
#include "../TextureGeneratorSelector/TextureGeneratorSelector.h"

#include "../Resources/ResourceManager/TextureResourceManager/TextureResourceManager.h"
#include "../Resources/ResourceManager/ShaderResourceManager/ShaderResourceManager.h"

#include "SceneResourceManager\SceneResourceManager.h"
#include "SceneMaker\SceneMaker.h"

#include "../Resources/ResourceData/MaterialData/MaterialData.h"
#include "../Resources/ResourceData/TextureData/TextureData.h"
#include "../Resources/ResourceData/GeometryData/GeometryData.h"
#include "../Resources/ResourceData/ShaderData/ShaderData.h"


//	Default SceneECS Constructor.
SceneECS::SceneECS(std::shared_ptr<ComponentMaker> newComponentMaker, std::shared_ptr<MainResourceManager> newResourceManager) : ECS(newComponentMaker)
{
	sceneResourceManager = std::dynamic_pointer_cast<SceneResourceManager>(newResourceManager);
}


SceneECS::~SceneECS()
{

}

//	Initialization of the ECS.
void SceneECS::initializeECS()
{

	//	Link the Event Queue with the Scene Resource Manager.
	sceneResourceManager->linkEventQueue(getEventQueue());

	//	Initialize the InteractionGenerationSystem.
	inputSystem = std::make_shared<InputSystem>(getEntityManager(),  getEventQueue());
	inputSystem->initializeSystem();

	interactionMovementResponseSystem = std::make_shared<InteractionMovementResponseSystem>(getEntityManager(),  getEventQueue());
	interactionMovementResponseSystem->initializeSystem();


	//	Initialize the Transform System.
	transformSystem = std::make_shared<TransformSystem>(getEntityManager(),  getEventQueue());
	transformSystem->initializeSystem();

	//	Initialize the Camera System.
	cameraSystem = std::make_shared<CameraSystem>(getEntityManager(),  getEventQueue());
	cameraSystem->initializeSystem();

	//	Initialize the Rendering System.
	renderingSystem = std::make_shared<RenderingSystem>(getEntityManager(),  getEventQueue());
	renderingSystem->initializeSystem();


	//	Create the Geometry, Material, Light, Texture and Shader Resource Manager.
	textureResourceManager = std::make_shared<TextureResourceManager>(getEventQueue());
	shaderResourceManager = std::make_shared<ShaderResourceManager>(getEventQueue());

	sceneMaker = std::make_shared<SceneMaker>(getEntityManager());

	//	Initialize the Scene.
	initializeScene();

	//	Register the Systems.
	ECS::registerSystem(inputSystem);
	ECS::registerSystem(interactionMovementResponseSystem);
	ECS::registerSystem(transformSystem);
	ECS::registerSystem(cameraSystem);
	ECS::registerSystem(renderingSystem);

	//	Dispatch the ECS_START_EVENT to the Event Queue.
	getDispatcher()->dispatchToEventQueue(EventType::ECS_START_EVENT, "GLOBAL", ComponentType::NO_COMPONENT, 0);
}

//	Load the Resources From a given file.
void SceneECS::loadResourcesFromFile(const std::string & resourceFile)
{
	//	Parse the Resource Description File.
	rdfp.parseResourceDescriptionFile(resourceFile, resources);

	//	Iterate over all the resources.
	for (auto resourcesItr = resources.begin(); resourcesItr != resources.end(); resourcesItr++)
	{
		processResource(resourcesItr->second);
	}
}

//	Load the Scene From File.
void SceneECS::loadSceneFromfile(const std::string & sceneFile)
{
	sceneMaker->loadSceneFromFile(sceneFile);
}

//	Process the Resource.
void SceneECS::processResource(const ResourceDescription & currentResourceDescription)
{
	//	Get the appropriate Resource Type.
	std::string resourceType = "None";
	bool hasType = currentResourceDescription.findProperty("Resource Type", resourceType);

	//	Check if we actually have the type, and can use it to appropriately process the data.
	if (hasType)
	{
		//	Material Resource.
		if (resourceType == "Material")
		{
			sceneResourceManager->loadResource(currentResourceDescription);
		}

		//	OpenGL Shader Resource.
		if (resourceType == "OpenGL Shader")
		{
			shaderResourceManager->processResource(currentResourceDescription);
		}

		//	Texture Resource.
		if (resourceType == "Texture")
		{
			textureResourceManager->processResource(currentResourceDescription);
		}

		if (resourceType == "OBJ")
		{
			sceneResourceManager->loadResource(currentResourceDescription);
		}

	}
	else
	{
		std::cout << "Error! SceneECS: Process Resource - Resource Has No Type! " << std::endl;
	}
}

//	Process the provided input.
void SceneECS::processInput(const InputType & ecsKey, const InputEventType & inputEventType, const EventType & eventType)
{
	inputSystem->processInput(ecsKey, inputEventType, eventType);
}

//	Update the ECS.
void SceneECS::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//
	ECS::update(deltaTime, currentFrameTime, lastFrameTime);
}

//	Shut Down the Demo ECS.
void SceneECS::shutDownECS()
{
	//	Destroy the Input System.
	inputSystem->shutDownSystem();

	//	Destroy the Interaction Movement System.
	interactionMovementResponseSystem->shutDownSystem();

	//	Destroy the CameraSystem.
	cameraSystem->shutDownSystem();

	//	Destroy the Transform System.
	transformSystem->shutDownSystem();

	//	Destroy the Rendering System.
	renderingSystem->shutDownSystem();
}

//	Miscellaneous clean up of the Systems.
void SceneECS::destroyECS()
{
	//	Destroy the Input System.
	inputSystem->destroySystem();

	//	Destroy the Interaction Movement System.
	interactionMovementResponseSystem->destroySystem();

	//	Destroy the CameraSystem.
	cameraSystem->destroySystem();

	//	Destroy the Transform System.
	transformSystem->destroySystem();

	//	Destroy the Rendering System.
	renderingSystem->destroySystem();
}

//	Initialize the Scene.
void SceneECS::initializeScene()
{
	//	Create the Light Entity.
	lightEntity = getEntityManager()->createEntity();
	getEntityManager()->addComponentToEntity(lightEntity, ComponentType::HIERARCHY_COMPONENT);
	getEntityManager()->addComponentToEntity(lightEntity, ComponentType::TRANSFORM_COMPONENT);
	getEntityManager()->addComponentToEntity(lightEntity, ComponentType::LIGHT_COMPONENT);

	//	Transform Component.
	std::shared_ptr<TransformComponent> lightTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(lightEntity, ComponentType::TRANSFORM_COMPONENT, "NO_MODULE"));
	lightTransformComponent->getTransform()->setScale(glm::vec3(1.0, 1.0, 1.0));
	lightTransformComponent->getTransform()->setPosition(glm::vec3(5.0, 15.0, 0.0));

	//	Light Component.
	std::shared_ptr<LightComponent> lightComponent = std::dynamic_pointer_cast<LightComponent>(getEntityManager()->getComponentOfEntity(lightEntity, ComponentType::LIGHT_COMPONENT, "NO_MODULE"));
}

//	Initialize the Camera Views.
void SceneECS::initializeCameraViews()
{
	////	Create the Camera Entity.
	//cameraEntity1 = getEntityManager()->createEntity();
	//getEntityManager()->addComponentToEntity(cameraEntity1, ComponentType::HIERARCHY_COMPONENT);
	//getEntityManager()->addComponentToEntity(cameraEntity1, ComponentType::TRANSFORM_COMPONENT);
	//getEntityManager()->addComponentToEntity(cameraEntity1, ComponentType::CAMERA_COMPONENT);

	//std::shared_ptr<TransformComponent> cameraTransformComponent1 = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(cameraEntity1, ComponentType::TRANSFORM_COMPONENT, "NO_MODULE"));
	//cameraTransformComponent1->getTransform()->setPosition(glm::vec3(50.0, 50.0, 50.0));
	//cameraTransformComponent1->getTransform()->setLookAtPoint(glm::vec3(0.0, 0.0, 0.0));

	////	Create the Camera Entity.
	//cameraEntity2 = getEntityManager()->createEntity();
	//getEntityManager()->addComponentToEntity(cameraEntity2, ComponentType::HIERARCHY_COMPONENT);
	//getEntityManager()->addComponentToEntity(cameraEntity2, ComponentType::TRANSFORM_COMPONENT);
	//getEntityManager()->addComponentToEntity(cameraEntity2, ComponentType::CAMERA_COMPONENT);

	//std::shared_ptr<TransformComponent> cameraTransformComponent2 = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(cameraEntity2, ComponentType::TRANSFORM_COMPONENT, "NO_MODULE"));
	//cameraTransformComponent2->getTransform()->setPosition(glm::vec3(-50.0, 50.0, 50.0));
	//cameraTransformComponent2->getTransform()->setLookAtPoint(glm::vec3(0.0, 0.0, 0.0));

	////	Create the Camera Entity.
	//cameraEntity3 = getEntityManager()->createEntity();
	//getEntityManager()->addComponentToEntity(cameraEntity3, ComponentType::HIERARCHY_COMPONENT);
	//getEntityManager()->addComponentToEntity(cameraEntity3, ComponentType::TRANSFORM_COMPONENT);
	//getEntityManager()->addComponentToEntity(cameraEntity3, ComponentType::CAMERA_COMPONENT);

	//std::shared_ptr<TransformComponent> cameraTransformComponent3 = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(cameraEntity3, ComponentType::TRANSFORM_COMPONENT, "NO_MODULE"));
	//cameraTransformComponent3->getTransform()->setPosition(glm::vec3(-50.0, 50.0, -50.0));
	//cameraTransformComponent3->getTransform()->setLookAtPoint(glm::vec3(0.0, 0.0, 0.0));

	////	Create the Camera Entity.
	//cameraEntity4 = getEntityManager()->createEntity();
	//getEntityManager()->addComponentToEntity(cameraEntity4, ComponentType::HIERARCHY_COMPONENT);
	//getEntityManager()->addComponentToEntity(cameraEntity4, ComponentType::TRANSFORM_COMPONENT);
	//getEntityManager()->addComponentToEntity(cameraEntity4, ComponentType::CAMERA_COMPONENT);

	//std::shared_ptr<TransformComponent> cameraTransformComponent4 = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(cameraEntity4, ComponentType::TRANSFORM_COMPONENT, "NO_MODULE"));
	//cameraTransformComponent4->getTransform()->setPosition(glm::vec3(50.0, 50.0, -50.0));
	//cameraTransformComponent4->getTransform()->setLookAtPoint(glm::vec3(0.0, 0.0, 0.0));
}
