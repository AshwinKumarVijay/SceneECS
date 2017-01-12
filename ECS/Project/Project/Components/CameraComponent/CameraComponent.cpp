#include "CameraComponent.h"



//	Default CameraComponent Constructor
CameraComponent::CameraComponent()
	:Component(ComponentType::CAMERA_COMPONENT, ComponentTypeRequirement::CAMERA_COMPONENT_REQUIREMENTS)
{
	//	Near Clip.
	nearClip = 0.01f;

	//	Far Clip.
	farClip = 500.0f;

	//	Aspect Ratio.
	aspectRatio = 1920.0f / 1080.0f;

	//	Field of View.
	FOV = glm::pi<float>() / 4.0f;

	//	Set this Camera to be inactive by default.
	isActive = false;
}
	
//	Default CameraComponent Destructor
CameraComponent::~CameraComponent()
{

}

//	Set this camera to be the active camera.
void CameraComponent::setActive()
{
	isActive = true;
}

//	Set this camera to be inactive.
void CameraComponent::setInactive()
{
	isActive = false;
}

//	Return whether this camera is active.
bool CameraComponent::getIsActive() const
{
	return isActive;
}

//	Return the Near Clip.
float CameraComponent::getNearClip() const
{
	return nearClip;
}

//	Set the Near Clip.
void CameraComponent::setNearClip(float newNearClip)
{
	nearClip = newNearClip;
}

//	Return the Far Clip.
float CameraComponent::getFarClip() const
{
	return farClip;
}

//	Set the Far Clip.
void CameraComponent::setFarClip(float newFarClip)
{
	farClip = newFarClip;
}

//	Return the FOV.
float CameraComponent::getFOV() const
{
	return FOV;
}

//	Set the FOV.
void CameraComponent::setFOV(float newFOV)
{
	FOV = newFOV;
}

//	Return the AspectRatio.
float CameraComponent::getAspectRatio() const
{
	return aspectRatio;
}

//	Set the AspectRatio.
void CameraComponent::setAspectRatio(float newAspectRatio)
{
	aspectRatio = newAspectRatio;
}


