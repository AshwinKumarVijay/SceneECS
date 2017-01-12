#include "Transform.h"


//	Default Transform Constructor
Transform::Transform()
{
	//	Initialize the Position, the Scale and the Rotation to basic default values.
	transformPosition = glm::vec3(0.0);
	transformScale = glm::vec3(1.0);
	transformRotation = glm::quat();

	//	Initialize the Transform Matrix and the Hierarchy Transform Matrix to the Identity Matrix.
	transformMatrix = std::make_shared<glm::mat4x4>(1.0f);
	hierarchyTransformMatrix = std::make_shared<glm::mat4>(1.0f);
	dirtyMatrixFlag = true;
}

//	Default Transform Destructor
Transform::~Transform()
{

}

//	Translate the transform by some amount.
void Transform::translateBy(const glm::vec3 & moveAmount)
{
	transformPosition = transformPosition + moveAmount;
	dirtyMatrixFlag = true;
}

//	Scale the transform by some amount.
void Transform::scaleBy(const glm::vec3 & scaleAmount)
{
	transformScale = transformScale * scaleAmount;
	dirtyMatrixFlag = true;
}

//	Rotate this Transform
void Transform::rotateBy(const float angleRad, const glm::vec3 & axis)
{

	transformRotation = glm::angleAxis(angleRad, glm::normalize(axis)) * transformRotation;
	dirtyMatrixFlag = true;
}

//	Set the position of this Transform.
void Transform::setPosition(const glm::vec3 & newTransformPosition)
{
	transformPosition = glm::vec3(newTransformPosition);
	dirtyMatrixFlag = true;
}

//	Set the vector representing the scale of the transform.
void Transform::setScale(const glm::vec3 & newTransformScale)
{
	transformScale = glm::vec3(newTransformScale);
	dirtyMatrixFlag = true;
}

//	Set the rotation of this Transform.
void Transform::setRotation(const glm::quat & newTransformRotation)
{
	transformRotation = glm::quat(newTransformRotation);
	dirtyMatrixFlag = true;
}

//	Compute the Transform Matrix.
void Transform::computeTransformMatrix()
{
	glm::mat4x4 positionMatrix = glm::mat4x4();
	positionMatrix = glm::translate(positionMatrix, transformPosition);

	glm::mat4x4 scaleMatrix = glm::mat4x4();
	scaleMatrix = glm::scale(scaleMatrix, transformScale);

	*transformMatrix = positionMatrix *  glm::mat4_cast(transformRotation) * scaleMatrix;
	dirtyMatrixFlag = false;
}

//	Compute the Hierarchy Transform Matrix.
void Transform::computeHierarchyTransformMatrix(const glm::mat4 & hierarchyMatrix)
{
	computeTransformMatrix();
	*hierarchyTransformMatrix = (hierarchyMatrix) * (*transformMatrix);
}

//	Return the vector represeting the translation of the transform.
glm::vec3 Transform::getPosition() const
{
	return transformPosition;
}

//	Return the vector representing the scale of the transform.
glm::vec3 Transform::getScale() const
{
	return transformScale;
}

//	Return the quaternion representing the rotation of the transform.
glm::quat Transform::getRotation() const
{
	return transformRotation;
}

//	Return the vector representing the foward direction of the transform.
glm::vec3 Transform::getFowardDirection() const
{
	//	Construct the new foward vector by rotating from the default forward direction.	
	return glm::normalize(glm::vec3(glm::mat4_cast(transformRotation) * glm::vec4(0.0, 0.0, -1.0, 0.0)));
}

//	Return the vector representing the right of the transform.
glm::vec3 Transform::getRightVector() const
{
	//	Construct the new right direction by rotating from the default right direciton.
	return glm::normalize(glm::vec3(glm::mat4_cast(transformRotation) * glm::vec4(1.0, 0.0, 0.0, 0.0)));
}

//	Return the vector representing the upward direction of the transform.
glm::vec3 Transform::getUpVector() const
{
	//	Construct the new up direction by rotating from the default up direciton.
	return glm::normalize(glm::vec3(glm::mat4_cast(transformRotation) * glm::vec4(0.0, 1.0, 0.0, 0.0)));
}

//	Return a pointer to the Transform Matrix.
std::shared_ptr<glm::mat4x4> Transform::getTransformMatrix() const
{
	return transformMatrix;
}

//	Return a pointer to the Hierarchical Transform Matrix.
std::shared_ptr<glm::mat4x4> Transform::getHierarchyTransformMatrix() const
{
	return hierarchyTransformMatrix;
}

//	Set the Foward Direction of the Transform to be toward a particular point.
void Transform::setLookAtPoint(const glm::vec3 & newLookAtPoint)
{
	//	Construct the new lookAt Direction.
	glm::vec3 lookAtDirection = glm::normalize(newLookAtPoint - getPosition());

	//	Construct the new Right Direction.
	glm::vec3 newRightDirection = glm::normalize(glm::cross(lookAtDirection, glm::vec3(0.0, 1.0, 0.0)));

	//	Construct the new Up Direction.
	glm::vec3 newUp = glm::normalize(glm::cross(newRightDirection, lookAtDirection));

	//	Generate the new Look At Rotation.
	glm::quat lookAtRotation = glm::rotation(getFowardDirection(), lookAtDirection);

	//	Generate the compensating Up Rotatx	ion.
	glm::quat upRotation = glm::rotation(lookAtRotation * getUpVector(), newUp);

	//	Construct the new rotation.
	setRotation(normalize(normalize(upRotation) * normalize(lookAtRotation) * transformRotation));
}
