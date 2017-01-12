#pragma once

#include <memory>

#include "glm\glm.hpp"
#include "glm\matrix.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtx\quaternion.hpp"


class Transform
{

public:

	//	Default Transform Constructor
	Transform();

	//	Default Transform Destructor
	virtual ~Transform();

	//	The vector by which we want to move this transform.
	void translateBy(const glm::vec3 & moveAmount);

	//	The vector by which we want to scale this transform.
	void scaleBy(const glm::vec3 & scaleAmount);

	//	Rotate this Transform by some amount around the axis.
	void rotateBy(const float angleRad, const glm::vec3 & axis);

	//	Set the position of the Transform.
	void setPosition(const glm::vec3 & newTransformPosition);

	//	Set the scale of the Transform.
	void setScale(const glm::vec3 & newTransformScale);

	//	Set the quaternion representing the rotation of the Transform.
	void setRotation(const glm::quat & newTransformRotation);

	//	Set the new Look At Point of the Transform, from its current position.
	void setLookAtPoint(const glm::vec3 & newLookAtPoint);
	
	//	Compute the Transform Matrix of this Transform.
	void computeTransformMatrix();
	
	//	Compute the Hierarchy Transform Matrix of this Transform, using the provided Hierarchy Matrix.
	void computeHierarchyTransformMatrix(const glm::mat4 & hierarchyMatrix);

	//	Return the current position of the Transform.
	glm::vec3 getPosition() const;

	//	Return the current scale of the Transform.
	glm::vec3 getScale() const;

	//	Return the current rotation of the Transform.
	glm::quat getRotation() const;

	//	Return the current forward direction of the Transform.
	glm::vec3 getFowardDirection() const;

	//	Return the current right direction of the Transform.
	glm::vec3 getRightVector() const;

	//	Return the current local up vector of the Transform.
	glm::vec3 getUpVector() const;

	//	Returns the Transform Matrix.
	std::shared_ptr<glm::mat4x4> getTransformMatrix() const;

	//	Return the Hierarchy Transform Matrix.
	std::shared_ptr<glm::mat4x4> getHierarchyTransformMatrix() const;

private:

	//	The vector representing the position of the transform.
	glm::vec3 transformPosition;

	//	The vector representing the scale of the transform.
	glm::vec3 transformScale;

	//	The quaternion representing the rotation of the transform.
	glm::quat transformRotation;

	//	The Transform Matrix representing the Translation * Rotation * Scale.
	std::shared_ptr<glm::mat4x4> transformMatrix;

	//	The Transform Matrix representing the Translation * Rotation * Scale, relative to the provided Hierarchy Matrix.
	std::shared_ptr<glm::mat4x4> hierarchyTransformMatrix;

	//	The boolean representing whether the Transform Matrix, currently accurately depicts the current Position, Scale and Rotation. 
	bool dirtyMatrixFlag;
};

