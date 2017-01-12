#pragma once


#include "../StringModifiers/StringModifiers.h"
#include "../ECS/ECS.h"

#include "../TypesList/EventTypes.h"
#include "../TypesList/EntityState.h"
#include "../TypesList/InputTypes.h"
#include "../TypesList/ComponentTypes.h"
#include "../TypesList/ResourceTypes.h"

#include "../RDFP/RDFP.h"

class System;
class TransformSystem;
class RenderingSystem;
class CameraSystem;
class InputSystem;
class InteractionMovementResponseSystem;
class MovementSystem;

class GeometryGeneratorSelector;
class TextureGeneratorSelector;

class GeometryResourceManager;
class MaterialResourceManager;
class TextureResourceManager;
class ShaderResourceManager;

class SceneResourceManager;
class SceneMaker;

class MaterialData;
class TextureData;
class LightData;
class GeometryData;
class ShaderData;


class SceneECS : public ECS
{

public:

	//	Default SceneECS Constructor.
	SceneECS(std::shared_ptr<ComponentMaker> newComponentMaker, std::shared_ptr<MainResourceManager> newResourceManager);

	//	Default SceneECS Destructor.
	virtual ~SceneECS();

	//	Initialization of the ECS.
	virtual void initializeECS();

	//	Load the Resources From a given file.
	virtual void loadResourcesFromFile(const std::string & resourceFile);
	virtual void loadSceneFromfile(const std::string & sceneFile);

	//	Process the Resource.
	virtual void processResource(const ResourceDescription & currentResourceDescription);

	//	Process the provided input.
	virtual void processInput(const InputType & ecsKey, const InputEventType & inputEventType, const EventType & eventType);

	//	Update the ECS.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Shut Down the Demo ECS.
	virtual void shutDownECS();

	//	Miscellaneous clean up of the Systems.
	virtual void destroyECS();

private:

	//	Initialize the Scene.
	virtual void initializeScene();

	//	Initialize the Camera Views.
	virtual void initializeCameraViews();


	//	The Interaction Generation System associated with the DemoECS.
	std::shared_ptr<InputSystem> inputSystem;

	//	The Interaction Movement Response System associated with the DemoECS.
	std::shared_ptr<InteractionMovementResponseSystem> interactionMovementResponseSystem;

	//	The Camera System associated with the DemoECS.
	std::shared_ptr<CameraSystem> cameraSystem;

	//	The Transform System associated with the DemoECS.
	std::shared_ptr<TransformSystem> transformSystem;

	//	The Rendering System associated with the DemoECS.
	std::shared_ptr<RenderingSystem> renderingSystem;

	//	Texture Resource Manager
	std::shared_ptr<TextureResourceManager> textureResourceManager;

	//	Shader Resource Manager
	std::shared_ptr<ShaderResourceManager> shaderResourceManager;

	//	The Scene Resource Manager.
	std::shared_ptr<SceneResourceManager> sceneResourceManager;

	//	The Scene Maker.
	std::shared_ptr<SceneMaker> sceneMaker;

	//	The Camera Views Entities.
	long int cameraEntity1;
	long int cameraEntity2;
	long int cameraEntity3;
	long int cameraEntity4;

	//	The Light Entity.
	long int lightEntity;

	//	The Resources and the Resource Description.
	std::map<std::string, ResourceDescription> resources;

	//	Resource Description File Parser.
	RDFP rdfp;
};

