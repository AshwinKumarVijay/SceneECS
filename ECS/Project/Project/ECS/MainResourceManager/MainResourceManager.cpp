#include "MainResourceManager.h"
#include "../DispatcherReceiver/EventDispatcher/EventDispatcher.h"


//	Default MainResourceManager Constructor.
MainResourceManager::MainResourceManager()
{

}

//	Default MainResourceManager Destructor.
MainResourceManager::~MainResourceManager()
{

}

//	Link the Event Queue. Associate the Event Dispatcher with the Event Queue.
void MainResourceManager::linkEventQueue(std::shared_ptr<EventQueue> newEventQueue)
{
	eventDispatcher = std::make_shared<EventDispatcher>(newEventQueue);
}

//	Dispatch the Event to the Event Queue.
void MainResourceManager::dispatchEventToEventQueue(std::shared_ptr<ECSEvent> newEvent)
{
	eventDispatcher->dispatchToEventQueue(newEvent);
}
