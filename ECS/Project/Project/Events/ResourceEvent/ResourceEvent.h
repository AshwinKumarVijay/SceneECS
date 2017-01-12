#pragma once

#include "../ECS/ECSEvent/ECSEvent.h"
#include "../Resources/ResourceData/ResourceData.h"

class ResourceEvent : public ECSEvent
{
public:

	//	Default ResourceEvent Constructor.
	ResourceEvent(const ResourceType & newResourceType, const ResourceEventType & newResourceEventType, const std::string & newModuleOrigin, const std::string & newResourceName, std::shared_ptr<const ResourceData> newResourceData);
	
	//	Default ResourceEvent Destructor.
	~ResourceEvent();

	//	Return the ResourceType.
	ResourceType getResourceType() const;

	//	Return the ResourceEventType.
	ResourceEventType getResourceEventType() const;

	//	Return the Resource Name.
	std::string getResourceName() const;

	//	Return the Resource Data.
	std::shared_ptr<const ResourceData> getResourceData() const;
	

private:

	//	The Resource Type associated with this Event.
	ResourceType resourceType;

	//	The Resource Event Type assocaited with this Event
	ResourceEventType resourceEventType;

	//	The Resource Name associated with this Event.
	std::string resourceName;

	//	The Resource Data ass0ciated with this Event.
	std::shared_ptr<const ResourceData> resourceData;

};

