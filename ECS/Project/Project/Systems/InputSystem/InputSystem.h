#pragma once

#include <string>
#include <iostream>

#include "../ECS/System/System.h"
#include "../../TypesList/EventTypes.h"
#include "../../TypesList/EntityState.h"
#include "../../TypesList/InputTypes.h"
#include "../../TypesList/ComponentTypes.h"
#include "../../TypesList/ResourceTypes.h"

class Component;
class HierarchyComponent;
class TransformComponent;
class PhysicsComponent;
class GeometryComponent;
class MaterialComponent;
class RenderingComponent;
class CameraComponent;


class ECSEvent;
class InputEvent;


class InputSystem : public System
{

public:

	//	Default InputSystem Constructor
	InputSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);

	//	Default InputSystem Destructor.
	virtual ~InputSystem();

	//	Initialize the InputSystem.
	virtual void initializeSystem();

	//	Update the InputSystem.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Process the Input Provided, and generate the corresponding event.
	virtual void processInput(const InputType & newInputType, const InputEventType & newInputEventType, const EventType & newEventType);

	//	Shut Down the InputSystem.
	virtual void shutDownSystem();

	//	Clean up the InputSystem.
	virtual void destroySystem();




protected:

	//	Process the Events in the InputSystem.
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);


private:


};

