#include "ResourceManager.h"
#include "../ECS/EventQueue/EventQueue.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"


//	Default ResourceManager Constructor
ResourceManager::ResourceManager(std::shared_ptr<EventQueue> newEventQueue, const std::string & newManagerTypeSignature)
{
	//	Get the Event Queue.
	eventQueue = newEventQueue;

	//	Assign the Manager Type Signature.
	managerTypeSignature = newManagerTypeSignature;

	//	Create the Event Dispatcher and link it with the Event Queue.
	eventDispatcher = std::make_shared<EventDispatcher>(eventQueue);
}

//	Default ResourceManager Destructor
ResourceManager::~ResourceManager()
{


}

//
std::shared_ptr<EventDispatcher> ResourceManager::getDispatcher() const
{
	return eventDispatcher;
}
