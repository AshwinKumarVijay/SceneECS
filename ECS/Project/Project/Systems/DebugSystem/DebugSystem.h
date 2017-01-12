#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../ECS/System/System.h"

class DebugSystem : public System
{
public:

	//	Default DebugSystem Constructor
	DebugSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue);


	//	Default DebugSystem Destructor
	virtual ~DebugSystem();


	//	 Miscellaneous initialization of the System.
	virtual void initializeSystem();

	//	Update the System - implementation depends on the inheritance.
	virtual void update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);

	//	Shut Down the System.
	virtual void shutDownSystem();

	//	cleanUpSystem
	virtual void destroySystem();


protected:

	//	Process the Events that have occurred.
	virtual void processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime);


private:

	//	The StringStream for the Debug Output.
	std::stringstream debugOutputStream;

	//	Frame Counter Variables. 
	int frameCount;

	//	The last print time of the FPS.
	float lastPrintTime;

};
