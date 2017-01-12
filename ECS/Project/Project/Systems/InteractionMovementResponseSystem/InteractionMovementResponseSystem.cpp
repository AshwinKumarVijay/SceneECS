#include "InteractionMovementResponseSystem.h"

#include "../../ECS/EntityManager/EntityManager.h"
#include "../../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"


#include "../../ECS/ECSEvent/ECSEvent.h"

#include "../../Events/InteractionEvent/InteractionEvent.h"

#include "../../ECS/Component/Component.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../Transform/Transform.h"
#include "../Components/MovementResponseComponent/MovementResponseComponent.h"

//	Default Interaction Movement Response System Constructor
InteractionMovementResponseSystem::InteractionMovementResponseSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	: System(newEntityManager, newEventQueue, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM")
{

}

//	Default Interaction Movement Response System Destructor
InteractionMovementResponseSystem::~InteractionMovementResponseSystem()
{

}

//	Initialize the Interaction Movement Response System.
void InteractionMovementResponseSystem::initializeSystem()
{

}

//	Update the Interaction Movement Response System.
void InteractionMovementResponseSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Process Events.
	processEvents(deltaTime, currentFrameTime, lastFrameTime);
}

//	Process the Events.
void InteractionMovementResponseSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	//	Check if there are any Events.
	while (getReceiver()->getNumberOfEvents() > 0)
	{
		//	Get the events.
		std::shared_ptr<const ECSEvent> nextEvent = getReceiver()->getNextEvent();

		//	Process the Interaction Events.
		processInteractionEvents(nextEvent);

		//	Respond to the System shutdown.
		if (nextEvent->getEventType() == EventType::ECS_SHUTDOWN_EVENT)
		{
			//	Shut Down the Interaction Movement Response System.
			shutDownSystem();
		}
	}
}

//	Process Any Interaction Events.
void InteractionMovementResponseSystem::processInteractionEvents(std::shared_ptr<const ECSEvent> nextEvent)
{

	if (nextEvent->getEventType() == EventType::INTERACTION_EVENT)
	{
		//	Cast the next ECSEvent to the next Interaction Event.
		std::shared_ptr<const InteractionEvent> nextInteractionEvent = std::dynamic_pointer_cast<const InteractionEvent>(nextEvent);

		//	Get the EntityManager.
		std::shared_ptr<EntityManager> entityManager = getEntityManager();

		//	Get the entities with a Transform Component.
		std::shared_ptr<std::vector<long int>> entities = entityManager->getEntitiesWithComponentOfType(ComponentType::MOVEMENT_RESPONSE_COMPONENT);

		//	If there are no entities, we do not really have to do anything.
		if (entities != NULL)
		{
			//	Iterate over the entities, and process them.
			for (auto currentEntity : *entities)
			{
				//	View the Movement Response Component.
				std::shared_ptr<const MovementResponseComponent> movementResponseComponent = std::dynamic_pointer_cast<const MovementResponseComponent>(entityManager->viewComponentOfEntity(currentEntity, ComponentType::MOVEMENT_RESPONSE_COMPONENT));

				if (movementResponseComponent->getIsActive())
				{
					//	Interaction Event Type - Move Foward.
					if (nextInteractionEvent->getInteractionEventType() == InteractionEventType::MOVE_FORWARD)
					{
						std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM"));

						//	Get the Transform Component Direction.
						glm::vec3 direction = transformComponent->getTransform()->getFowardDirection();

						//	Compute the Movement Step.
						glm::vec3 moveStep = movementResponseComponent->getForwardMovementCoefficient() * direction;

						//	Translate the Transform Component.
						transformComponent->getTransform()->translateBy(moveStep);

					}	//	Interaction Event Type - Move Backward.
					else if (nextInteractionEvent->getInteractionEventType() == InteractionEventType::MOVE_BACKWARD)
					{
						std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM"));

						//	Get the Transform Component Direction.
						glm::vec3 direction = transformComponent->getTransform()->getFowardDirection();

						//	Compute the Movement Step.
						glm::vec3 moveStep = movementResponseComponent->getBackwardMovementCoefficient() * -1.0f * direction;

						//	Translate the Transform Component.
						transformComponent->getTransform()->translateBy(moveStep);

					}	//	Interaction Event Type - Move Left.
					else if (nextInteractionEvent->getInteractionEventType() == InteractionEventType::MOVE_LEFT)
					{
						std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM"));

						//	Get the Transform Component Direction.
						glm::vec3 direction = transformComponent->getTransform()->getRightVector();

						//	Compute the Movement Step.
						glm::vec3 moveStep = movementResponseComponent->getLeftMovementCoefficient() * -1.0f * direction;

						//	Translate the Transform Component.
						transformComponent->getTransform()->translateBy(moveStep);

					}	//	Interaction Event Type - Move Right.
					else if (nextInteractionEvent->getInteractionEventType() == InteractionEventType::MOVE_RIGHT)
					{
						std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM"));

						//	Get the Transform Component Direction.
						glm::vec3 direction = transformComponent->getTransform()->getRightVector();

						//	Compute the Movement Step.
						glm::vec3 moveStep = movementResponseComponent->getRightMovementCoefficient() * direction;

						//	Translate the Transform Component.
						transformComponent->getTransform()->translateBy(moveStep);
					}
					else if (nextInteractionEvent->getInteractionEventType() == InteractionEventType::ROLL_RIGHT)
					{
						//	
						std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM"));

						//	Get the Transform Component Direction.
						glm::vec3 axis = transformComponent->getTransform()->getFowardDirection();

						//	Compute the Rotation Step.
						float rotationStep = movementResponseComponent->getRollCoefficient();

						//	Translate the Transform Component.
						transformComponent->getTransform()->rotateBy(rotationStep, axis);

					}
					else if (nextInteractionEvent->getInteractionEventType() == InteractionEventType::ROLL_LEFT)
					{
						//	
						std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM"));

						//	Get the Transform Component Direction.
						glm::vec3 axis = transformComponent->getTransform()->getFowardDirection();

						//	Compute the Rotation Step.
						float rotationStep = -movementResponseComponent->getRollCoefficient();

						//	Translate the Transform Component.
						transformComponent->getTransform()->rotateBy(rotationStep, axis);
					}
					else if (nextInteractionEvent->getInteractionEventType() == InteractionEventType::PITCH_UP)
					{
						//	
						std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM"));

						//	Get the Transform Component Direction.
						glm::vec3 axis = transformComponent->getTransform()->getRightVector();

						//	Compute the Rotation Step.
						float rotationStep = movementResponseComponent->getPitchCoefficient();

						//	Translate the Transform Component.
						transformComponent->getTransform()->rotateBy(rotationStep, axis);
					}
					else if (nextInteractionEvent->getInteractionEventType() == InteractionEventType::PITCH_DOWN)
					{
						//	
						std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM"));

						//	Get the Transform Component Direction.
						glm::vec3 axis = transformComponent->getTransform()->getRightVector();

						//	Compute the Rotation Step.
						float rotationStep = -movementResponseComponent->getPitchCoefficient();

						//	Translate the Transform Component.
						transformComponent->getTransform()->rotateBy(rotationStep, axis);
					}
					else if (nextInteractionEvent->getInteractionEventType() == InteractionEventType::YAW_RIGHT)
					{
						//	
						std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM"));

						//	Get the Transform Component Direction.
						glm::vec3 axis = transformComponent->getTransform()->getUpVector();

						//	Compute the Rotation Step.
						float rotationStep = movementResponseComponent->getYawCoefficient();

						//	Translate the Transform Component.
						transformComponent->getTransform()->rotateBy(rotationStep, axis);
					}
					else if (nextInteractionEvent->getInteractionEventType() == InteractionEventType::YAW_LEFT)
					{
						//	
						std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "INTERACTION_MOVEMENT_RESPONSE_SYSTEM"));

						//	Get the Transform Component Direction.
						glm::vec3 axis = transformComponent->getTransform()->getUpVector();

						//	Compute the Rotation Step.
						float rotationStep = -movementResponseComponent->getYawCoefficient();

						//	Translate the Transform Component.
						transformComponent->getTransform()->rotateBy(rotationStep, axis);
					}
				}
			}
		}
	}
}

//	Shut down the Interaction Movement Response System.
void InteractionMovementResponseSystem::shutDownSystem()
{

}

//	Clean up the Interaction Movement Response System.
void InteractionMovementResponseSystem::destroySystem()
{

}



