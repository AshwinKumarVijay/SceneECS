#include "System.h"
#include "../EventQueue/EventQueue.h"
#include "../DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../DispatcherReceiver/EventReceiver/EventReceiver.h"

//	Default System Constructor
System::System(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue, const std::string & newSystemTypeSignature)
{
	
	entityManager = newEntityManager;
	eventQueue = newEventQueue;
	systemTypeSignature = newSystemTypeSignature;
	eventDispatcher = std::make_shared<EventDispatcher>(newEventQueue);
	eventReceiver = std::make_shared<EventReceiver>();
	eventQueue->addReceiver(eventReceiver);
}


//	Default System Destructor
System::~System()
{
	entityManager = NULL;
	
	eventQueue = NULL;
	
	eventDispatcher = NULL;
	
	eventReceiver = NULL;
}

//	Default Event processing does nothing.
void System::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{

}

//	Return a pointer to the EntityManager this System is using.
std::shared_ptr<EntityManager> System::getEntityManager() const
{
	return entityManager;
}

//	Return a pointer to the EventQueue this System is using.
std::shared_ptr<EventQueue> System::getEventQueue() const
{
	return eventQueue;
}

std::shared_ptr<EventDispatcher> System::getDispatcher() const
{
	return eventDispatcher;
}

std::shared_ptr<EventReceiver> System::getReceiver() const
{
	return eventReceiver;
}

//	Return the System Type Signature.
std::string System::getSystemTypeSignature() const
{
	return systemTypeSignature;
}
