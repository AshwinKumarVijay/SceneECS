#pragma once

#include <memory>
#include <string>

class Configuration;

class EntityManager;
class Component;

class MainResourceManager;

class EventQueue;
class ECSEvent;
class EventDispatcher;
class EventReceiver;



class System
{

public:
	
	//	Default System Constructor.
	System(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue, const std::string & newSystemTypeSignature);

	//	Default System Destructor.
	virtual ~System();

	//	Initialize the System.
	virtual void initializeSystem() = 0;

	//	Update the System.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime) = 0;

	//	Shut Down the System.
	virtual void shutDownSystem() = 0;

	//	Destroy the System.
	virtual void destroySystem() = 0;

	//	Return the EntityManager.
	std::shared_ptr<EntityManager> getEntityManager() const;

	//	Return the Event Queue.
	std::shared_ptr<EventQueue> getEventQueue() const;

	//	Return the Event Dispatcher.
	std::shared_ptr<EventDispatcher> getDispatcher() const;

	//	Return the Dispatcher Receiver.
	std::shared_ptr<EventReceiver> getReceiver() const;

	//	Return the Main Resource Manager.
	std::shared_ptr<MainResourceManager> getResourceManager() const;

	//	Return the System Type Signature.
	std::string getSystemTypeSignature() const;

protected:

	//	Process the Events.
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime) = 0;


private:

	//	The EntityManager that this system will refer to.
	std::shared_ptr<EntityManager> entityManager;

	//	The EventQueue that this system will refer to.
	std::shared_ptr<EventQueue> eventQueue;

	//	Used to dispatch Events to the Event Queue.
	std::shared_ptr<EventDispatcher> eventDispatcher;

	//	Used to Receive Events from the Event Queue.
	std::shared_ptr<EventReceiver> eventReceiver;

	//	The Signature representing the System Type
	std::string systemTypeSignature;
};

