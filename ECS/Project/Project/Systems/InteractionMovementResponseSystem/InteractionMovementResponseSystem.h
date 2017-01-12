#pragma once

#include "../ECS/System/System.h"

class Event;
class InteractionEvent;

class Component;
class HierarchyComponent;
class TransformComponent;
class PhysicsComponent;
class GeometryComponent;
class MaterialComponent;
class RenderingComponent;
class CameraComponent;
class SelectionComponent;


class InteractionMovementResponseSystem : public System
{

public:
	
	//	Add Comments - TO DO
	InteractionMovementResponseSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);

	//	Add Comments - TO DO
	virtual ~InteractionMovementResponseSystem();

	//	Add Comments - TO DO
	virtual void initializeSystem();

	//	Add Comments - TO DO
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Add Comments - TO DO
	virtual void shutDownSystem();

	//	Add Comments - TO DO
	virtual void destroySystem();


protected:

	//	Add Comments - TO DO
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Add Comments - TO DO
	virtual void processInteractionEvents(std::shared_ptr<const ECSEvent> nextEvent);

private:
		


};

