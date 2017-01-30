#include "InputSystem.h"

#include "../../ECS/EntityManager/EntityManager.h"
#include "../../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../../ECS/ECSEvent/ECSEvent.h"
#include "../ECS/EventQueue/EventQueue.h"

#include "../../ECS/EntityManager/EntityManager.h"
#include "../../ECS/ECSEvent/ECSEvent.h"
#include "../../Events/InputEvent/InputEvent.h"
#include "../../Events/InteractionEvent/InteractionEvent.h"

#include "../../ECS/Component/Component.h"


//	Default InteractionGenerationSystem Constructor
InputSystem::InputSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	: System(newEntityManager, newEventQueue, "INPUT_SYSTEM")
{

}

//	Default InteractionGenerationSystem Destructor
InputSystem::~InputSystem()
{

}

//	Initialize the InteractionGenerationSystem
void InputSystem::initializeSystem()
{

}

//	Update the InteractionGenerationSystem
void InputSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	processEvents(deltaTime, currentFrameTime, lastFrameTime);
}

//	Process the Input.
void InputSystem::processInput(const InputType & newInputType, const InputEventType & newInputEventType, const EventType & newEventType)
{
	//	Check if the event is an Input Event.
	if (newEventType == EventType::INPUT_EVENT)
	{
		//	
		if (newInputEventType == InputEventType::INPUT_KEY_PRESS)
		{
			//	Check what the InputType, the Key Pressed, is.
			switch (newInputType)
			{

			//	Move Forward.
			case InputType::KEY_W:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::MOVE_FORWARD, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);
				break;
			}

			//	Move Backward.
			case InputType::KEY_S:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::MOVE_BACKWARD, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);
				break;
			}

			//	Move Left.
			case InputType::KEY_A:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::MOVE_LEFT, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);
				break;
			}

			//	Move Right.
			case InputType::KEY_D:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::MOVE_RIGHT, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);
				break;
			}

			//	Yaw Left.
			case InputType::KEY_Q:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::YAW_LEFT, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);
				break;
			}

			//	Yaw Right.
			case InputType::KEY_E:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::YAW_RIGHT, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);
				break;
			}


			//	Roll left.
			case InputType::KEY_LEFT:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::ROLL_LEFT, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);
				break;
			}

			//	Roll Right.
			case InputType::KEY_RIGHT:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::ROLL_RIGHT, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);
				break;
			}


			//	No Camera.
			case InputType::KEY_K:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::NO_CAMERA, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);

				std::cout << "NO CAMERA" << std::endl;

				break;
			}

			//	Previous Camera.
			case InputType::KEY_J:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::PREVIOUS_CAMERA, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);

				std::cout << "PREVIOUS CAMERA" << std::endl;

				break;
			}

			//	Next Camera.
			case InputType::KEY_L:
			{
				std::shared_ptr<InteractionEvent> newInteractionEvent = std::make_shared<InteractionEvent>(InteractionEventType::NEXT_CAMERA, "INPUT_SYSTEM");
				getDispatcher()->dispatchToEventQueue(newInteractionEvent);

				std::cout << "NEXT CAMERA" << std::endl;

				break;
			}

			//	
			default:
				break;

			}
		}
	}
}

//	Process the Events.
void InputSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Check if there are any Events.
	while (getReceiver()->getNumberOfEvents() > 0)
	{
		//	Get the events.
		std::shared_ptr<const ECSEvent> nextEvent = getReceiver()->getNextEvent();

		//	Respond to the System shutdown.
		if (nextEvent->getEventType() == EventType::ECS_SHUTDOWN_EVENT)
		{
			shutDownSystem();
		}
	}
}

//	Shut Down the InteractionGenerationSystem.
void InputSystem::shutDownSystem()
{

}

//	Clean Up the InteractionGenerationSystem
void InputSystem::destroySystem()
{

}
