#include "EventDispatcher.h"

#include "../../ECSEvent/ECSEvent.h"
#include "../../EventQueue/EventQueue.h"

//	Default EventDispatcher Constructor.
EventDispatcher::EventDispatcher(std::shared_ptr<EventQueue> newEventQueue)
{
	eventQueue = newEventQueue;
}

//	Default EventDispatcher Destructor.
EventDispatcher::~EventDispatcher()
{

}

//	Dispatch the Event to the EventQueue.
void EventDispatcher::dispatchToEventQueue(std::shared_ptr<const ECSEvent> newEvent) const
{
	//	Dispatch the Event to the EventQueue.
	eventQueue->queueEvent(newEvent);
}

//	Create and dispatch the Event to the EventQueue.
void EventDispatcher::dispatchToEventQueue(const EventType & newEventType, const std::string & newSystemOrigin, const ComponentType & newComponentType, const long int & newEntityID) const
{
	//	Create the Event as specified by the ECSEvent queue.
	std::shared_ptr<ECSEvent> newEvent = std::make_shared<ECSEvent>(newEventType, newSystemOrigin, newComponentType, newEntityID);

	//	Dispatch the Event to the EventQueue.
	dispatchToEventQueue(newEvent);
}
