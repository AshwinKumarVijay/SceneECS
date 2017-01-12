#pragma once

#include <memory>

#include "../TypesList/EventTypes.h"
#include "../TypesList/EntityState.h"
#include "../TypesList/InputTypes.h"
#include "../TypesList/ComponentTypes.h"
#include "../TypesList/ResourceTypes.h"

#include "../StringModifiers/StringModifiers.h"

#include "../ECS/ECSEvent/ECSEvent.h"
#include "../Events/InputEvent/InputEvent.h"
#include "../Events/ResourceEvent/ResourceEvent.h"

#include "../RDFP/ResourceDescription.h"

class EventQueue;
class EventDispatcher;

class ResourceManager
{

public:


	//	Default ResourceManager Constructor
	ResourceManager(std::shared_ptr<EventQueue> newEventQueue, const std::string & newSystemTypeSignature);

	//	Default ResourceManager Destructor
	virtual ~ResourceManager();

	//	Resource Management Functions.
	virtual void processResource(const ResourceDescription & newResourceDescription) = 0;

	//	Returns the DispatcherReceiver that this Resource Manager is using.
	std::shared_ptr<EventDispatcher> getDispatcher() const;



private:

	//	The EventQueue that this system will refer to.
	std::shared_ptr<EventQueue> eventQueue;

	//	Used to dispatch Events to the Event Queue.
	std::shared_ptr<EventDispatcher> eventDispatcher;

	//	The Signature representing the Manager Type
	std::string managerTypeSignature;

};

