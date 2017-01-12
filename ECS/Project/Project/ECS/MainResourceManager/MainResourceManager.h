#pragma once
#include <memory>

class EventQueue;
class EventReceiver;
class EventDispatcher;
class ECSEvent;

class MainResourceManager : public std::enable_shared_from_this<MainResourceManager>
{

public:

	//	Default MainResourceManager Constructor.
	MainResourceManager();

	//	Default MainResourceManager Destructor.
	virtual ~MainResourceManager();

	//	Link the Event Queue. Associate the Event Dispatcher with the Event Queue.
	virtual void linkEventQueue(std::shared_ptr<EventQueue> newEventQueue);

	//	Dispatch the Resource Event to the Event Queue.
	virtual void dispatchEventToEventQueue(std::shared_ptr<ECSEvent> newEvent);

private:

	//	The Associated Event Dispatcher.
	std::shared_ptr<EventDispatcher> eventDispatcher;

};

