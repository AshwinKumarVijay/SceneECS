#include "ResourceEvent.h"


//	Default ResourceEvent Constructor
ResourceEvent::ResourceEvent(const ResourceType & newResourceType, const ResourceEventType & newResourceEventType,  const std::string & newModuleOrigin, const std::string & newResourceName, std::shared_ptr<const ResourceData> newResourceData)
	: ECSEvent(EventType::RESOURCE_EVENT, newModuleOrigin, ComponentType::NO_COMPONENT, -1)

{
	//	Assign the Resource Type associated with this Resource Event.
	resourceType = newResourceType;

	//	Assign the Resource Event Type associated with this Resource Event.
	resourceEventType = newResourceEventType;

	//	Assign the Resource Name associated with this Resource Event.
	resourceName = newResourceName;

	//	Assign the Resource Data associated with this Resource Event.
	resourceData = newResourceData;
}

//	Default ResourceEvent Destructor
ResourceEvent::~ResourceEvent()
{

}

//	Return the Ressource Name.
std::string ResourceEvent::getResourceName() const
{
	return resourceName;
}

//	Return the Data associated with the Resource.
std::shared_ptr<const ResourceData> ResourceEvent::getResourceData() const
{
	return resourceData;
}

//	Return the ResourceType associated with this resource.
ResourceType ResourceEvent::getResourceType() const
{
	return resourceType;
}

//	Return the ResourceEventType associated with this ResourceEventType.
ResourceEventType ResourceEvent::getResourceEventType() const
{
	return resourceEventType;
}
