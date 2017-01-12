#pragma once

#include "../ECS/ECSEvent/ECSEvent.h"

class InteractionEvent : public ECSEvent
{

public:

	//	Add Comments - TO DO
	InteractionEvent(const InteractionEventType & newInteractionEvent, const std::string & newModuleOrigin);

	//	Add Comments - TO DO
	virtual ~InteractionEvent();

	//	Add Comments - TO DO
	InteractionEventType getInteractionEventType() const;

private:

	//	The Interaction Event Type.
	InteractionEventType interactionEventType;

};

