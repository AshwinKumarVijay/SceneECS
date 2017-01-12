#pragma once

#include <vector>
#include <memory>
#include <map>

#include "glm\glm.hpp"
#include "../ResourceData.h"

class btDefaultMotionState;
class btRigidBody;

class PhysicsData : public ResourceData
{

public:

	//	Default PhysicsData Constructor.
	PhysicsData();

	//	Default PhysicsData Destructor
	virtual ~PhysicsData();


private:


};

