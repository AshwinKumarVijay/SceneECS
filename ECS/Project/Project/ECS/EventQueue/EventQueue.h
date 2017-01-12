#pragma once

#include <vector>
#include <map>
#include <memory>

class EventReceiver;
class ECSEvent;

class EventQueue
{
public:

	/**

	Name: EventQueue
	Parameters: -
	Purpose: Default EventQueue Constructor
	Return Value: -
	Other Output: -

	*/
	EventQueue();


	/**

	Name: ~EventQueue
	Parameters: -
	Purpose: Default EventQueue Destructor
	Return Value: -
	Other Output: -

	*/
	virtual ~EventQueue();


	/**

	Name: addDispatcher
	Parameters:
	- "newDispatcher" - (weak_ptr<Dispatcher>) - A new dispatcher that can add events to the event queue.
	Purpose: Add a dispatcher to the Event Queue.
	Return Value: -
	Other Output: -

	*/
	virtual void addReceiver(std::weak_ptr<EventReceiver> newDispatcher);



	/**

	Name: queueEvent
	Parameters:
	- "newEvent" - (Event) (const) (&) - A new event to send to the event queues.
	Purpose: Sends the events to the queues.
	Return Value: -
	Other Output: -

	*/
	virtual void queueEvent(const std::shared_ptr<const ECSEvent> ecsEvent) const;


	/**

	Name: cleanEventQueue
	Parameters: -
	Purpose: Clean up the EventQueue.
	Return Value: -
	Other Output: -

	*/
	virtual void cleanEventQueue();



private:

	//	A list of DispatcherReceivers.
	std::vector<std::weak_ptr<EventReceiver>> eventReceivers;
	
};

