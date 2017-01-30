#include "CameraControlSystem.h"
#include "../ECS/EntityManager/EntityManager.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../ECS/ECSEvent/ECSEvent.h"
#include "../Events/InputEvent/InputEvent.h"
#include "../Events/InteractionEvent/InteractionEvent.h"

#include "../../Components/CameraComponent/CameraComponent.h"
#include "../../Components/TransformComponent/TransformComponent.h"
#include "../../Transform/Transform.h"


//	Default CameraControlSystem Constructor.
CameraControlSystem::CameraControlSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	:System(newEntityManager, newEventQueue, "CAMERA_CONTROL_SYSTEM")
{
	activeCameraEntityID = -1;
}

//	Default CameraControlSystem Destructor.
CameraControlSystem::~CameraControlSystem()
{

}

//	Initialize the System.
void CameraControlSystem::initializeSystem()
{

}

//	Update the System.
void CameraControlSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	processEvents(deltaTime, currentFrameTime, lastFrameTime);
}

//	Shut down the System.
void CameraControlSystem::shutDownSystem()
{

}

//	Destroy the System.
void CameraControlSystem::destroySystem()
{

}

//	Process the Events.
void CameraControlSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
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
		else
		{
			//	Check whether we have an Interaction Event.
			if (nextEvent->getEventType() == EventType::INTERACTION_EVENT)
			{
				processInteractionEvents(nextEvent);
			}

			//	Check if the Camera has Changed, because of some other system.
			if (nextEvent->getEventType() == EventType::COMPONENT_CHANGED && nextEvent->getComponentType() == ComponentType::CAMERA_COMPONENT && nextEvent->getModuleOrigin() != "CAMERA_CONTROL_SYSTEM")
			{
				//	Get the Camera Component.
				std::shared_ptr<const CameraComponent> cameraComponent = std::dynamic_pointer_cast<const CameraComponent>(getEntityManager()->viewComponentOfEntity(nextEvent->getEntityID(), ComponentType::CAMERA_COMPONENT));

				//	Get the Entity ID, and the Active Camera ID.
				if (nextEvent->getEntityID() == activeCameraEntityID && !cameraComponent->getIsActive())
				{
					activeCameraEntityID = -1;

					std::cout << activeCameraEntityID << std::endl;
				}
				else
				{

					if (cameraComponent->getIsActive())
					{
						activeCameraEntityID = nextEvent->getEntityID();
					
					}
				}
			}
		}
	}
}

//
void CameraControlSystem::processInteractionEvents(std::shared_ptr<const ECSEvent> nextEvent)
{
	//	Cast to an Interaction Event.
	std::shared_ptr<const InteractionEvent> interactionEvent = std::dynamic_pointer_cast<const InteractionEvent>(nextEvent);

	//	
	if (activeCameraEntityID != -1)
	{
		if (interactionEvent->getInteractionEventType() == InteractionEventType::MOVE_RIGHT)
		{

			//	Get the Camera Transform Component.
			std::shared_ptr<TransformComponent> cameraTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(activeCameraEntityID, ComponentType::TRANSFORM_COMPONENT, "CAMERA_CONTROL_SYSTEM"));
		
			//	Move the Camera to the Right.
			cameraTransformComponent->getTransform()->setPosition(cameraTransformComponent->getTransform()->getPosition() + glm::vec3(1.0, 0.0, 0.0));

		}
		else if (interactionEvent->getInteractionEventType() == InteractionEventType::MOVE_LEFT)
		{
			//	Get the Camera Transform Component.
			std::shared_ptr<TransformComponent> cameraTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(activeCameraEntityID, ComponentType::TRANSFORM_COMPONENT, "CAMERA_CONTROL_SYSTEM"));

			//	Move the Camera to the Left.
			cameraTransformComponent->getTransform()->setPosition(cameraTransformComponent->getTransform()->getPosition() + glm::vec3(-1.0, 0.0, 0.0));
		}
		else if (interactionEvent->getInteractionEventType() == InteractionEventType::MOVE_FORWARD)
		{
			//	Get the Camera Transform Component.
			std::shared_ptr<TransformComponent> cameraTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(activeCameraEntityID, ComponentType::TRANSFORM_COMPONENT, "CAMERA_CONTROL_SYSTEM"));

			//	Move the Camera Forward.
			cameraTransformComponent->getTransform()->setPosition(cameraTransformComponent->getTransform()->getPosition() + glm::vec3(0.0, 0.0, 1.0));
		}
		else if (interactionEvent->getInteractionEventType() == InteractionEventType::MOVE_BACKWARD)
		{
			//	Get the Camera Transform Component.
			std::shared_ptr<TransformComponent> cameraTransformComponent = std::dynamic_pointer_cast<TransformComponent>(getEntityManager()->getComponentOfEntity(activeCameraEntityID, ComponentType::TRANSFORM_COMPONENT, "CAMERA_CONTROL_SYSTEM"));

			//	Move the Camera Backward.
			cameraTransformComponent->getTransform()->setPosition(cameraTransformComponent->getTransform()->getPosition() + glm::vec3(0.0, 0.0, -1.0));
		}
	}
}

