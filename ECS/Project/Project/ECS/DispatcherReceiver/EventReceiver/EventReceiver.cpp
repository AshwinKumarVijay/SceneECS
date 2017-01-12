#include "EventReceiver.h"

#include "../../ECSEvent/ECSEvent.h"
#include "../../EventQueue/EventQueue.h"

//	Default EventReceiver Constructor.
EventReceiver::EventReceiver()
{

}

//	Default EventReceiver Destructor.
EventReceiver::~EventReceiver()
{

}

void EventReceiver::receiveFromEventQueue(std::shared_ptr<const ECSEvent> newEvent)
{
	events.push(newEvent);
}

std::shared_ptr<const ECSEvent> EventReceiver::getNextEvent()
{
	//	Check the number of remaining events.
	if (getNumberOfEvents() == 0)
	{
		//	Return NULL if there are no remaining events.
		return NULL;
	}
	else
	{
		//	If there are remaining events, return it, and pop it off the queue.
		std::shared_ptr<const ECSEvent> nextEvent = events.front();
		events.pop();
		return nextEvent;
	}
}

int EventReceiver::getNumberOfEvents()
{
	return (int)events.size();
}

//	Clear the Events.
void EventReceiver::clearEvents()
{
	while (!events.empty())
	{ 
		events.pop();
	}
}
