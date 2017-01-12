#include "ECSEvent.h"


//	Default Event Constructor
ECSEvent::ECSEvent(const EventType & newEventType, const std::string & newModuleOrigin, const ComponentType & newComponentType, const long int & newEntityID)
{
	eventType = newEventType;
	systemOrigin = newModuleOrigin;
	componentType = newComponentType;
	entityID = newEntityID;
}

//	Default Event Destructor
ECSEvent::~ECSEvent()
{

}

//	Return the EventType associated with the ECSEvent.
EventType ECSEvent::getEventType() const
{
	return eventType;
}

//	Return the SystemType associated with the ECSEvent.
std::string ECSEvent::getModuleOrigin() const
{
	return systemOrigin;
}

//	Return the ComponentType associated with the ECSEvent.
ComponentType ECSEvent::getComponentType() const
{
	return componentType;
}

//	Return the Entity ID associated with the ECSEvent.
long int ECSEvent::getEntityID() const
{
	return entityID;
}
