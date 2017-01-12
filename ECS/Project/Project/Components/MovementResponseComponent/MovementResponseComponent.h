#pragma once

#include "../ECS/Component/Component.h"

class MovementResponseComponent : public Component
{

public:

	//	Add Comments - TO DO
	MovementResponseComponent();

	//	Add Comments - TO DO
	virtual ~MovementResponseComponent();


	//	Add Comments - TO DO
	float getForwardMovementCoefficient() const;

	//	Add Comments - TO DO
	virtual void setForwardMovementCoefficient(const float & newForwardMovementCoefficient);

	//	Add Comments - TO DO
	float getBackwardMovementCoefficient() const;

	//	Add Comments - TO DO
	virtual void setBackwardMovementCoefficient(const float & newBackwardMovementCoefficient);

	//	Add Comments - TO DO
	float getLeftMovementCoefficient() const;

	//	Add Comments - TO DO
	virtual void setLeftMovementCoefficient(const float & newLeftMovementCoefficient);

	//	Add Comments - TO DO
	float getRightMovementCoefficient() const;

	//	Add Comments - TO DO
	virtual void setRightMovementCoefficient(const float & newRightMovementCoefficient);

	//	Add Comments - TO DO
	float getRollCoefficient() const;

	//	Add Comments - TO DO
	virtual void setRollCoefficient(const float & newRollCoefficient);

	//	Add Comments - TO DO
	float getPitchCoefficient() const;

	//	Add Comments - TO DO
	virtual void setPitchCoefficient(const float & newPitchCoefficient);

	//	Add Comments - TO DO
	float getYawCoefficient() const;

	//	Add Comments - TO DO
	virtual void setYawCoefficient(const float & newYawCoefficient);

	//	Add Comments - TO DO
	virtual bool getIsActive() const;

	//	Add Comments - TO DO
	virtual void setActive();

	//	Add Comments - TO DO
	virtual void setInactive();

private:

	//	The Coefficient for Foward Movement.
	float forwardMovementCoefficient;

	//	The Coefficient for Backward Movement.
	float backwardMovementCoefficient;

	//	The Coefficient for Left Movement.
	float leftMovementCoefficient;

	//	The Coefficient for the Right Movement.
	float rightMovementCoefficient;

	//	The Coefficient for Roll.
	float rollCoefficient;

	//	The Coefficient for Pitch.
	float pitchCoefficient;

	//	The Coefficient for Yaw.
	float yawCoefficient;

	//	Whether this Movement Response is Active.
	bool active;
};

