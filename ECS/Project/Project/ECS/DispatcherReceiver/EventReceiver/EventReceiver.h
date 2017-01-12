#pragma once

#include <vector>
#include <memory>
#include <stack>
#include <queue>

#include "../TypesList/EventTypes.h"
#include "../TypesList/EntityState.h"
#include "../TypesList/ComponentTypes.h"

class EventQueue;
class ECSEvent;

class EventReceiver
{
public:

	//	Default EventReceiver Constructor.
	EventReceiver();

	//	Default EventReceiver Destructor.
	virtual ~EventReceiver();

	//	Receive an event from the event queue.
	virtual void receiveFromEventQueue(std::shared_ptr<const ECSEvent> newEvent);

	//	Return the Next Event in the eventQueue.
	std::shared_ptr<const ECSEvent> getNextEvent();

	//	Return the number of events in the event receiver queue.
	int getNumberOfEvents();

	//	Clear the Events.
	void clearEvents();

private:

	//	 List of Events.
	std::queue<std::shared_ptr<const ECSEvent>> events;

};

