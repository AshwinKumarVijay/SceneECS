#include "EventQueue.h"
#include "../DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../ECSEvent/ECSEvent.h"

//	Default EventQueue Constructor
EventQueue::EventQueue()
{

}

//	Default EventQueue Destructor
EventQueue::~EventQueue()
{

}

//	Add a dispatcher to the list of dispatchers who can set events.
void EventQueue::addReceiver(std::weak_ptr<EventReceiver> newReceiver)
{
	eventReceivers.push_back(newReceiver);
}


//	Add a event - sending it to the list of receivers.
void EventQueue::queueEvent(const std::shared_ptr<const ECSEvent> newEvent) const
{
	//	Iterate over all the receivers, and send the event to each of them.
	for (unsigned int i = 0; i < eventReceivers.size(); i++)
	{
		std::shared_ptr<EventReceiver> currentReceiver = eventReceivers[i].lock();
		if (currentReceiver != NULL)
		{
			currentReceiver->receiveFromEventQueue(newEvent);
		}
	}
}

//	Clean up the Event Queue.
void EventQueue::cleanEventQueue()
{
	eventReceivers.clear();
}
