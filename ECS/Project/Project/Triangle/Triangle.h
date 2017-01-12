#pragma once

#include "glm\glm.hpp"

class Triangle
{
	
public:
	//	Default Triangle Constructor.
	Triangle(glm::vec3 newA, glm::vec3 newB, glm::vec3 newC);

	//	Default Triangle Destructor.
	virtual ~Triangle();

	//	Compute and return the Normal for this Face.
	glm::vec3 computeFaceNormal();

	//	Return the Vertex.
	glm::vec3 getA();
	glm::vec3 getB();
	glm::vec3 getC();

private:

	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;


};