#include "MovementResponseComponent.h"


//	Default Movement Response Component Constructor.
MovementResponseComponent::MovementResponseComponent()
	:Component(ComponentType::MOVEMENT_RESPONSE_COMPONENT, ComponentTypeRequirement::MOVEMENT_RESPONSE_COMPONENT_REQUIREMENTS)
{
	forwardMovementCoefficient = 1.0f;
	backwardMovementCoefficient = 1.0f;
	leftMovementCoefficient = 1.0f;
	rightMovementCoefficient = 1.0f;
	rollCoefficient = 0.1f;
	pitchCoefficient = 0.1f;
	yawCoefficient = 0.1f;
	active = true;
}

//	Default Movement Response Component Destructor.
MovementResponseComponent::~MovementResponseComponent()
{

}

//	Return the Forward Movement Coefficient.
float MovementResponseComponent::getForwardMovementCoefficient() const
{
	return forwardMovementCoefficient;
}

//	Set the Foward Movement Coefficient.
void MovementResponseComponent::setForwardMovementCoefficient(const float & newForwardMovementCoefficient)
{
	forwardMovementCoefficient = newForwardMovementCoefficient;
}

//	Return the Backward Movement Coefficient.
float MovementResponseComponent::getBackwardMovementCoefficient() const
{
	return backwardMovementCoefficient;
}

//	Set the Backward Movement Coefficient.
void MovementResponseComponent::setBackwardMovementCoefficient(const float & newBackwardMovementCoefficient)
{
	backwardMovementCoefficient = newBackwardMovementCoefficient;
}

//	Return the Left Movement Coefficient.
float MovementResponseComponent::getLeftMovementCoefficient() const
{
	return leftMovementCoefficient;
}

//	Set the Left Movement Coefficient.
void MovementResponseComponent::setLeftMovementCoefficient(const float & newLeftMovementCoefficient)
{
	leftMovementCoefficient = newLeftMovementCoefficient;
}


//	Return the Right Movement Coefficient.
float MovementResponseComponent::getRightMovementCoefficient() const
{
	return rightMovementCoefficient;
}

//	Set the Right Movement Coefficient.
void MovementResponseComponent::setRightMovementCoefficient(const float & newRightMovementCoefficient)
{
	rightMovementCoefficient = newRightMovementCoefficient;
}

//	Return the Roll Coefficient.
float MovementResponseComponent::getRollCoefficient() const
{
	return rollCoefficient;
}

//	Set the Roll Coefficient.
void MovementResponseComponent::setRollCoefficient(const float & newRollCoefficient)
{
	rollCoefficient = newRollCoefficient;
}

//	Return the Pitch Coefficient.
float MovementResponseComponent::getPitchCoefficient() const
{
	return pitchCoefficient;
}

//	Set the Pitch Coefficient.
void MovementResponseComponent::setPitchCoefficient(const float & newPitchCoefficient)
{
	pitchCoefficient = newPitchCoefficient;
}

//	Return the Yaw Coefficient.
float MovementResponseComponent::getYawCoefficient() const
{
	return yawCoefficient;
}

//	Set the Yaw Coefficient.
void MovementResponseComponent::setYawCoefficient(const float & newYawCoefficient)
{
	yawCoefficient = newYawCoefficient;
}

//	Return whether this Component is Active.
bool MovementResponseComponent::getIsActive() const
{
	return active;
}

//	Set this Component to be active.
void MovementResponseComponent::setActive()
{
	active = true;
}

//	Set this Component to be inactive.
void MovementResponseComponent::setInactive()
{
	active = false;
}
