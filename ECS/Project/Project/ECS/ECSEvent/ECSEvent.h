#pragma once

#include <vector>
#include <map>
#include <memory>

#include "../TypesList/EventTypes.h"
#include "../TypesList/EntityState.h"
#include "../TypesList/InputTypes.h"
#include "../TypesList/ComponentTypes.h"
#include "../TypesList/ResourceTypes.h"
#include "../TypesList/InteractionTypes.h"

class ECSEvent
{

public:

	/**

	Name: ECSEvent
	Parameters: 
	- "newEventType" - (EventType) (const) (&) - The EventType associated with this Event.
	- "newModuleOrigin" - (ModuleType) (const) (&) - The System sending out this Event.
	- "newComponentType" - (ComponentType) (const) (&) - The ComponentType, if there is one.
	- "newEntityID" - (long int) (const) (&) - The Entity associated, if there is one.
	Purpose: Default ECSEvent Constructor
	Return Value: -
	Other Output: -

	*/
	ECSEvent(const EventType & newEventType, const std::string & newModuleOrigin, const ComponentType & newComponentType, const long int & newEntityID);

	/**

	Name: ~ECSEvent
	Parameters: -
	Purpose: Default ECSEvent Destructor
	Return Value: -
	Other Output: -

	*/
	virtual ~ECSEvent();


	/**

	Name: getEventType
	Parameters: -
	Purpose: Return the EventType
	Return Value: 
	- (EventType) - The EventType.
	Other Output: -

	*/
	EventType getEventType() const;

	/**

	Name: getSystemOrigin
	Parameters: -
	Purpose: Return the system sending the Event.
	Return Value:
	- (ModuleType) - The SystemType sending this Event.
	Other Output: -

	*/
	std::string getModuleOrigin() const;

	/**

	Name: getComponentType
	Parameters: -
	Purpose: Return associated ComponentType.
	Return Value:
	- (ComponentType) - The ComponentType associated with this Event.
	Other Output: -

	*/
	ComponentType getComponentType() const;

	/**

	Name: getEntityID
	Parameters: -
	Purpose: Return associated EntityID.
	Return Value: 
	- (long int) - The ID of the Entity associated with this Event.
	Other Output: -

	*/
	long int getEntityID() const;


private:

	//	The EventType associated with this ECSEvent.
	EventType eventType;

	//	The SystemType associated with this ECSEvent.
	std::string systemOrigin;

	//	The ComponentType associated.
	ComponentType componentType;

	//	The EntityID associated with this ECSEvent.
	long int entityID;
};

