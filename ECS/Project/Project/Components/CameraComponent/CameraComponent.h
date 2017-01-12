#pragma once

#include "../ECS/Component/Component.h"
#include "../Camera/Camera.h"

struct CameraDescription
{	

};

class CameraComponent : public Component
{

public:

	//	Default CameraComponent Constructor.
	CameraComponent();

	//	Default CameraComponent Destructor.
	virtual ~CameraComponent();

	//	Set this CameraComponent to be active.
	void setActive();

	//	Set this CameraComponent to be inactive.
	void setInactive();

	//	Return whether this CameraComponent is Active.
	bool getIsActive() const;

	//	Return the Near Clip of this CameraComponent.
	float getNearClip() const;
	//	Set the Near Clip of this CameraComponent.
	void setNearClip(float newNearClip);

	//	Return the Far Clip of the CameraComponent.
	float getFarClip() const;
	//	Set the Far Clip of this CameraComponent.
	void setFarClip(float newFarClip);

	//	Return the Field of View of this CameraComponent.
	float getFOV() const;
	//	Set the Field of View of this CameraComponent.
	void setFOV(float newFOV);

	//	Return the Aspect Ration of this CameraComponent.
	float getAspectRatio() const;
	//	Set the Aspect Ratio of this CameraComponent.
	void setAspectRatio(float newAspectRatio);
	


private:

	//	Whether this CameraComponent is Active.
	bool isActive;

	//	The Near Clip of this Camera Component.
	float nearClip;
	//	The Far Clip of this Camera Component.
	float farClip;

	//	The Field of View of this Camera Component.
	float FOV;
	//	The Aspect Ratio of this Camera Component.
	float aspectRatio;
};

