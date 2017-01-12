#pragma once

#include "GL\glew.h"
#include "GLFW\glfw3.h"


#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"

class Camera
{
public:

	//	Add Comments- TO DO.
	Camera();
	//	Add Comments- TO DO.
	virtual ~Camera();

	//	Add Comments- TO DO.
	void updateCamera();

	//	Add Comments- TO DO.
	void updatePerspectiveMatrix();

	//	Add Comments- TO DO.
	void updateViewMatrix();

	//	Add Comments- TO DO.
	void setCameraPosition(glm::vec3 newPosition);
	//	Add Comments- TO DO.
	glm::vec3 getCameraPosition() const;

	//	Add Comments- TO DO.
	void setLookAtDirection(glm::vec3 newLookAtDirection);
	//	Add Comments- TO DO.
	glm::vec3 getLookAtDirection();

	//	Add Comments- TO DO.
	void setUpVector(glm::vec3 upVector);
	//	Add Comments- TO DO.
	glm::vec3 getUpVector();

	//	Add Comments - TO DO
	float getNearClip() const;
	//	Add Comments - TO DO
	void setNearClip(float newNearClip);

	//	Add Comments - TO DO
	float getFarClip() const;
	//	Add Comments - TO DO
	void setFarClip(float newFarClip);

	//	Add Comments - TO DO
	float getFOV() const;
	//	Add Comments - TO DO
	void setFOV(float newFOV);

	//	Add Comments - TO DO
	float getAspectRatio() const;
	//	Add Comments - TO DO
	void setAspectRatio(float newAspectRatio);


	//	Add Comments- TO DO.
	glm::mat4x4 getViewMatrix() const;
	//	Add Comments- TO DO.
	glm::mat4x4 getPerspectiveMatrix() const;


private:

	//	Add Comments- TO DO.
	glm::vec3 cameraPosition;
	//	Add Comments- TO DO.
	glm::vec3 lookAtPoint;

	//	Add Comments- TO DO.
	glm::vec3 upVector;

	//	Add Comments- TO DO.
	float nearClip;
	//	Add Comments- TO DO.
	float farClip;
	//	Add Comments- TO DO.

	//	Add Comments- TO DO.
	float FOV;
	//	Add Comments- TO DO.
	float aspectRatio;

	//	Add Comments- TO DO.
	glm::mat4x4 perspectiveMatrix;
	//	Add Comments- TO DO.
	glm::mat4x4 viewMatrix;
};

