#include "DebugSystem.h"


#include "../ECS/EntityManager/EntityManager.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../ECS/ECSEvent/ECSEvent.h"

//	Default DebugSystem Constructor
DebugSystem::DebugSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	:System(newEntityManager, newEventQueue, "DEBUG_SYSTEM")
{
	//	
	lastPrintTime = 0.0;
	frameCount = 0;
}

//	Default DebugSystem Destructor
DebugSystem::~DebugSystem()
{


}

//	Initialize the Debug System.
void DebugSystem::initializeSystem()
{


}

//	Update the Debug System.
void DebugSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	processEvents(deltaTime, currentFrameTime, lastFrameTime);
	frameCount++;
	lastPrintTime += deltaTime;
	if (lastPrintTime > 1.0)
	{
		std::cout << "FPS = " << frameCount << " Frames Per Second. " << std::endl;
		std::cout << "Time Per Frame = " << 1000.0 / (double(frameCount)) << " ms. " << std::endl;
		frameCount = 0;
		lastPrintTime = 0;
	}

}

//	Process the Events.
void DebugSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Check if there are available events.
	while (getReceiver()->getNumberOfEvents() > 0)
	{
		//	Get the next event.
		std::shared_ptr<const ECSEvent> nextEvent = getReceiver()->getNextEvent();
	}

}


//	Shut Down the System.
void DebugSystem::shutDownSystem()
{

}

//	Clean up the DebugSystem.
void DebugSystem::destroySystem()
{

}