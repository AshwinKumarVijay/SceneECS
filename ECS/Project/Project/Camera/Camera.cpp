#include "Camera.h"

Camera::Camera()
{
	cameraPosition = glm::vec3(70.0f, 70.0f, 70.0f);

	lookAtPoint = glm::vec3(0.0, 0.0, 0.0);

	upVector = glm::vec3(0.0f, 1.0f, 0.0f);

	nearClip = 0.01f;

	farClip = 1000.0f;
	
	aspectRatio = 1920.0f / 1080.0f;

	FOV = glm::pi<float>() / 3.0f;

	perspectiveMatrix = glm::perspective(FOV, aspectRatio, nearClip, farClip);

	viewMatrix = glm::lookAt(cameraPosition, lookAtPoint, upVector);
}

//	
void Camera::updateCamera()
{
	updatePerspectiveMatrix();

	updateViewMatrix();
}

//	
void Camera::updatePerspectiveMatrix()
{
	perspectiveMatrix = glm::perspective(FOV, aspectRatio, nearClip, farClip);
}

//	
void Camera::updateViewMatrix()
{
	viewMatrix = glm::lookAt(cameraPosition, lookAtPoint, upVector);
}

float Camera::getNearClip() const
{
	return nearClip;
}

//	
void Camera::setNearClip(float newNearClip)
{
	nearClip = newNearClip;
}

float Camera::getFarClip() const
{
	return farClip;
}

//	
void Camera::setFarClip(float newFarClip)
{
	farClip = newFarClip;
}

//	
void Camera::setLookAtDirection(glm::vec3 newLookAtDirection)
{
	lookAtPoint = cameraPosition + glm::normalize(newLookAtDirection);
}
//	
glm::vec3 Camera::getLookAtDirection()
{
	return glm::normalize(lookAtPoint - cameraPosition);
}

//	
void Camera::setUpVector(glm::vec3 newUpVector)
{
	upVector = newUpVector;
}

//	
glm::vec3 Camera::getUpVector()
{
	return upVector;
}

//	
void Camera::setCameraPosition(glm::vec3 newCameraPosition)
{
	cameraPosition = newCameraPosition;
}

//	
glm::vec3 Camera::getCameraPosition() const
{
	return cameraPosition;
}

//	
float Camera::getFOV() const
{
	return FOV;
}

//	
void Camera::setFOV(float newFOV)
{
	FOV = newFOV;
}

//	
float Camera::getAspectRatio() const
{
	return aspectRatio;
}

//	
void Camera::setAspectRatio(float newAspectRatio)
{
	aspectRatio = newAspectRatio;
}

//	
glm::mat4x4 Camera::getPerspectiveMatrix() const
{
	return perspectiveMatrix;
}

//	
glm::mat4x4 Camera::getViewMatrix() const
{
	return viewMatrix;
}

//	
Camera::~Camera()
{

}
