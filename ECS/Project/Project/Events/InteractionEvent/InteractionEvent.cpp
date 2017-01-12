#include "InteractionEvent.h"


//	Default InteractionEvent Constructor
InteractionEvent::InteractionEvent(const InteractionEventType & newInteractionEvent, const std::string & newModuleOrigin)
	: ECSEvent(EventType::INTERACTION_EVENT, newModuleOrigin, ComponentType::NO_COMPONENT, -1)
{
	interactionEventType = newInteractionEvent;
}

//	Default InteractionEvent Destructor
InteractionEvent::~InteractionEvent()
{

}

//	Return the InteractionEventType associated with this InteractionEvent.
InteractionEventType InteractionEvent::getInteractionEventType() const
{
	return interactionEventType;
}
