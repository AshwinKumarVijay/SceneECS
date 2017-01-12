#include "Triangle.h"

//	Default Triangle Constructor.
Triangle::Triangle(glm::vec3 newA, glm::vec3 newB, glm::vec3 newC)
{
	a = newA;
	b = newB;
	c = newC;
}

//	Default Triangle Destructor.
Triangle::~Triangle()
{

}

//	Compute and Return the Normal of this Triangle.
glm::vec3 Triangle::computeFaceNormal()
{
	glm::vec3 aTob = glm::normalize(b - a);
	glm::vec3 aToc = glm::normalize(c - a);

	return glm::normalize(glm::cross(aTob, aToc));
}

glm::vec3 Triangle::getA()
{
	return a;
}

glm::vec3 Triangle::getB()
{
	return b;
}

glm::vec3 Triangle::getC()
{
	return c;
}
