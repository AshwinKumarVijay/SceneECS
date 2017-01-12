#pragma once

#include "../ECS/ECSEvent/ECSEvent.h"

class InputEvent : public ECSEvent
{

public:
	
	//	Add Comments - TO DO
	InputEvent(const InputType & newInputType, const InputEventType & newInputEventType, const std::string & newModuleOrigin);

	//	Add Comments - TO DO
	~InputEvent();

	//	Return the Input Event Type associated with this InputEvent.
	InputEventType getInputEventType() const;

	//	Return the Input Type associated with this InputEvent.
	InputType getInputType() const;

	
private:

	//	The Input Event Type
	InputEventType inputEventType;

	//	The Input Type
	InputType inputType;	
};

