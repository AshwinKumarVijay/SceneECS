#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../ECS/System/System.h"

class Component;
class HierarchyComponent;
class TransformComponent;
class PhysicsComponent;
class GeometryComponent;
class MaterialComponent;
class RenderingComponent;
class CameraComponent;

class CameraSystem : public System
{

public:

	//	Default Camera System Constructor. The Entity Manager and the Event Queue the System will use.
	CameraSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);

	//	Default Camera System Destructor.
	virtual ~CameraSystem();

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

	//	Set the Next Camera.
	virtual void setNextCamera();

	//	Set the Previous Camera.
	virtual void setPreviousCamera();

	//	Set No Camera.
	virtual void setNoCamera();


private:

	//	Active Camera Entity.	
	long int activeCameraEntity;

};

