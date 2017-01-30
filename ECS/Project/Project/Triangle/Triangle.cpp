#include "Triangle.h"

//	Default Triangle Constructor.
Triangle::Triangle(glm::vec3 newA, glm::vec3 newB, glm::vec3 newC)
{
	vertexA = newA;
	vertexB = newB;
	vertexC = newC;
}

//	Default Triangle Destructor.
Triangle::~Triangle()
{

}

//	Compute and Return the Normal of this Triangle.
glm::vec3 Triangle::getTriangleNormal()
{
	glm::vec3 aTob = glm::normalize(vertexB - vertexA);
	glm::vec3 aToc = glm::normalize(vertexC - vertexA);

	return glm::normalize(glm::cross(aTob, aToc));
}

glm::vec3 Triangle::getVertexA()
{
	return vertexA;
}

glm::vec3 Triangle::getVertexB()
{
	return vertexB;
}

glm::vec3 Triangle::getVertexC()
{
	return vertexC;
}
