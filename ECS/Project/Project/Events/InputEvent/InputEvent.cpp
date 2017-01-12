#include "InputEvent.h"


//	Default Input Event Constructor
InputEvent::InputEvent(const InputType & newInputType, const InputEventType & newInputEventType, const std::string & newModuleOrigin)
	: ECSEvent(EventType::INPUT_EVENT, newModuleOrigin, ComponentType::NO_COMPONENT, -1)
{
	inputType = newInputType;
	inputEventType = newInputEventType;
}

//	Default Input Event Destructor
InputEvent::~InputEvent()
{

}

//	Return the InputEventType associated with this InputEvent.
InputEventType InputEvent::getInputEventType() const
{
	return inputEventType;
}

//	Return the InputType associated with this InputEvent.
InputType InputEvent::getInputType() const
{
	return inputType;
}

