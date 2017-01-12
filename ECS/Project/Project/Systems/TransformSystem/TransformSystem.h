#pragma once

#include "glm\glm.hpp"

#include "../ECS/System/System.h"

class Component;
class HierarchyComponent;
class TransformComponent;
class PhysicsComponent;
class GeometryComponent;
class MaterialComponent;
class RenderingComponent;
class CameraComponent;

class TransformSystem : public System
{

public:

	//	Default Transform System Constructor. The Entity Manager and the Event Queue the System will use.
	TransformSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);
	
	//	Default TransformSystem Destructor
	virtual ~TransformSystem();

	//	Miscellaneous initialization of the System.
	virtual void initializeSystem();

	//	Update the System - Compute the Transform Matrix Hierarchy of the scene.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	virtual void computeHierarchyTransformMatrix(long int currentEntity, const glm::mat4 & hierarchyMatrix);

	//	Shut Down the System.
	virtual void shutDownSystem();

	//	Destroy the System.
	virtual void destroySystem();

protected:

	//	Process the Events that have occurred.
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

private:



};

