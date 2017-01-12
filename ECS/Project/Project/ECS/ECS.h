#pragma once

#include <vector>
#include <memory>

class EntityManager;
class ComponentMaker;

class EventQueue;
class EventDispatcher;
class EventReceiver;

class MainResourceManager;
class System;


class ECS
{

public:

	//	Default ECS Constructor
	ECS(std::shared_ptr<ComponentMaker> newComponentMaker);
	
	//	Default ECS Destructor
	virtual ~ECS();

	//	Initialization of the ECS.
	virtual void initializeECS() = 0;

	//	Register a System, for the update cycle.
	virtual int registerSystem(std::shared_ptr<System> newSystem);

	//	Remove a System from the update cycle.
	virtual void deregisterSystem(const int & systemIndex);

	//	Update the ECS, and all associated systems.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Shut Down the ECS.
	virtual void shutDownECS() = 0;

	//	Destroy the ECS.
	virtual void destroyECS() = 0;


protected:


	//	Return a pointer to the asssociated EntityManager.
	virtual std::shared_ptr<EntityManager> getEntityManager() const;

	//	Return a pointer to the associated ComponentMaker.
	virtual std::shared_ptr<ComponentMaker> getComponentMaker() const;

	//	Return a pointer to the associated EventQueue.
	virtual std::shared_ptr<EventQueue> getEventQueue() const;

	//	Return a pointer to the associated EventDispatcher.
	virtual std::shared_ptr<EventDispatcher> getDispatcher() const;

	//	Return a pointer to the associated EventReceiver.
	virtual std::shared_ptr<EventReceiver> getReceiver() const;


private:

	//	The Associated Entity Manager
	std::shared_ptr<EntityManager> entityManager;

	//	The Associated ComponentMaker.
	std::shared_ptr<ComponentMaker> componentMaker;

	//	The Associated Event Queue.
	std::shared_ptr<EventQueue> eventQueue;

	//	The Associated Dispatcher.
	std::shared_ptr<EventDispatcher> eventDispatcher;

	//	The Associated Receiver.
	std::shared_ptr<EventReceiver> eventReceiver;


	//	The Associated List of Systems.
	std::vector<std::shared_ptr<System>> systems;

};

