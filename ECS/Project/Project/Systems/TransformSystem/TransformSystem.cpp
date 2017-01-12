#include "TransformSystem.h"

#include "../../ECS/EntityManager/EntityManager.h"
#include "../../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"
#include "../../ECS/ECSEvent/ECSEvent.h"

#include "../../ECS/Component/Component.h"

#include "../Transform/Transform.h"
#include "../Components/HierarchyComponent/HierarchyComponent.h"
#include "../Components/TransformComponent/TransformComponent.h"

#include "../../ECS/MainResourceManager/MainResourceManager.h"

//	Default TransformSystem Constructor
TransformSystem::TransformSystem(std::shared_ptr<EntityManager> newEntityManager, std::shared_ptr<EventQueue> newEventQueue)
	:System(newEntityManager, newEventQueue, "TRANSFORM_SYSTEM")
{


}

//	Default TransformSystem Destructor
TransformSystem::~TransformSystem()
{


}

//	Initialize System.
void TransformSystem::initializeSystem()
{


}

//	Update the Transform System.
void TransformSystem::update(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
{
	processEvents(deltaTime, currentFrameTime, lastFrameTime);

	//	Get the EntityManager.
	std::shared_ptr<EntityManager> entityManager = getEntityManager();

	//	Get the entities with a Transform Component.
	std::shared_ptr<std::vector<long int>> entities = entityManager->getEntitiesWithComponentOfType(ComponentType::HIERARCHY_COMPONENT);

	//	If there are no entities, we do not really have to do anything.
	if (entities != NULL)
	{
		//	Iterate over the entities, and process them.
		for (auto currentEntity : *entities)
		{
			//	Get the Hierarchy Component.
			std::shared_ptr<const HierarchyComponent> hierarchyComponent = std::dynamic_pointer_cast<const HierarchyComponent>(entityManager->viewComponentOfEntity(currentEntity, ComponentType::HIERARCHY_COMPONENT));

			//	Check if this entity does not have parent. 
			if (hierarchyComponent->getParent() == -1)
			{
				computeHierarchyTransformMatrix(currentEntity, glm::mat4(1.0));
			}
		}

	}
}

//	Compute the Hierarchy Transform Matrix.
void TransformSystem::computeHierarchyTransformMatrix(long int currentEntity, const glm::mat4 & hierarchyMatrix)
{
	//	Get the EntityManager.
	std::shared_ptr<EntityManager> entityManager = getEntityManager();
	
	//	Check if this is the currentEntity.
	if (currentEntity != -1)
	{
		//	Get the Hierarchy Component.
		std::shared_ptr<const HierarchyComponent> hierarchyComponent = std::dynamic_pointer_cast<const HierarchyComponent>(entityManager->viewComponentOfEntity(currentEntity, ComponentType::HIERARCHY_COMPONENT));

		//	Get the transform component.
		std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager->getComponentOfEntity(currentEntity, ComponentType::TRANSFORM_COMPONENT, "TRANSFORM_SYSTEM"));

		//	Compute the Hierarchy Component.
		if (hierarchyComponent != NULL && transformComponent != NULL)
		{
			//	Compute the transform.
			transformComponent->getTransform()->computeTransformMatrix();
			transformComponent->getTransform()->computeHierarchyTransformMatrix(hierarchyMatrix);

			//	Iterate over the entities lower on the hierarchy tree.
			for (auto currentChildEntity = hierarchyComponent->getChildEntities().begin(); currentChildEntity != hierarchyComponent->getChildEntities().end(); currentChildEntity++)
			{
				computeHierarchyTransformMatrix(*currentChildEntity, *transformComponent->getTransform()->getHierarchyTransformMatrix());
			}
		}
	}
}

//	Process the Events.
void TransformSystem::processEvents(const float & deltaTime, const float & currentFrameTime, const float & lastFrameTime)
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

//	Shut Down the System.
void TransformSystem::shutDownSystem()
{

}

//	Miscellaneous clean up the system.
void TransformSystem::destroySystem()
{


}
