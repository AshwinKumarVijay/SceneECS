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
	glm::vec3 getTriangleNormal();

	//	Return the Vertex.
	glm::vec3 getVertexA();
	glm::vec3 getVertexB();
	glm::vec3 getVertexC();

private:

	glm::vec3 vertexA;
	glm::vec3 vertexB;
	glm::vec3 vertexC;


};