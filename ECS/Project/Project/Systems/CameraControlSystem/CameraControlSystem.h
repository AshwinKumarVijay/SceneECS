#pragma once
#include <memory>
#include <iostream>

#include "../ECS/System/System.h"

class EntityManager;
class EventQueue;


class CameraControlSystem : public System
{

public:

	//	Default CameraControlSystem Constructor.
	CameraControlSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);

	//	Default CameraControlSystem Destructor.
	virtual ~CameraControlSystem();

	//	Initialize the System.
	virtual void initializeSystem();

	//	Update the System.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Shut down the System.
	virtual void shutDownSystem();

	//	Destroy the System.
	virtual void destroySystem();


protected:

	//	Process the Events.
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Process the Interaction Event.
	virtual void processInteractionEvents(std::shared_ptr<const ECSEvent> nextEvent);

private:

	long int activeCameraEntityID;

};

