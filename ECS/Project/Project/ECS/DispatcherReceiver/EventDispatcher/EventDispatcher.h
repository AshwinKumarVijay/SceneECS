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

class EventDispatcher
{

public:

	//	Default EventDispatcher Constructor.
	EventDispatcher(std::shared_ptr<EventQueue> newEventQueue);

	//	Default EventDispatcher Destructor.
	virtual ~EventDispatcher();

	//	
	virtual void dispatchToEventQueue(std::shared_ptr<const ECSEvent> newEvent) const;

	//	
	virtual void dispatchToEventQueue(const EventType & newEventType, const std::string & newSystemOrigin, const ComponentType & newComponentType, const long int & newEntityID) const;


private:

	//	Associated event queue.
	std::shared_ptr<EventQueue> eventQueue;


};

