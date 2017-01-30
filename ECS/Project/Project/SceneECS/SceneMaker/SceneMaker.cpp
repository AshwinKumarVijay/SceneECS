#include "SceneMaker.h"

#include "../../ECS/EntityManager/EntityManager.h"

#include "../../Components/HierarchyComponent/HierarchyComponent.h"
#include "../../Components/TransformComponent/TransformComponent.h"
#include "../../Components/GeometryComponent/GeometryComponent.h"
#include "../../Components/RenderingComponent/RenderingComponent.h"
#include "../../Components/LightComponent/LightComponent.h"

#include "../../Transform/Transform.h"

//	Default SceneMaker Constructor.
SceneMaker::SceneMaker(std::shared_ptr<EntityManager> newEntityManager)
{
	entityManager = newEntityManager;
}

//	Default SceneMaker Destructor.
SceneMaker::~SceneMaker()
{

}

//	Load the Scene From File.
bool SceneMaker::loadSceneFromFile(const std::string & SDF)
{
	//	The Scene Description Vector.
	std::vector<std::string> SDV;

	//	Open the file.
	std::ifstream filestream(SDF);

	//	The temporary line.
	std::string currentLine;

	//	Read in the file, one line at a time.
	while (std::getline(filestream, currentLine))
	{
		//	Add it to the actual description.
		SDV.push_back(StringModifiers::trimmed(currentLine));
	}

	//	Parse the description.
	std::cout << "Parsing " << SDF << " " << std::endl;;
	return runSDV(SDV);
}

//	Run the Scene Description Vector.
bool SceneMaker::runSDV(const std::vector<std::string>& SDV)
{
	//	Check if the provided description really is a resource description.
	if (SDV[0] != "#Scene Description File")
		std::cerr << "Error! Not A Scene Description File!" << std::endl;

	//	
	for (int i = 1; i < SDV.size(); i++)
	{
		//	Check if we should ignore the current line.
		if (shouldIgnoreLine(SDV[i]))
		{
			continue;
		}

		bool successfullyParsed = runSDVCommand(SDV[i]);
	
		if (!successfullyParsed)
		{
			std::cerr << "Error ! Failed to Parse Scene Description at line : " << i << std::endl;
			return false;
		}

	}
	
	return true;
}

//	Run the Current SDV Command.
bool SceneMaker::runSDVCommand(const std::string & currentCommand)
{
	std::vector<std::string> commandTokens = StringModifiers::split_string(currentCommand, " ");
	
	if (commandTokens[0] == "#Entity")
	{
		//	Entity Tokens.
		return runEntityCommand(commandTokens);
	}	
	else if (commandTokens[0] == "#Component")
	{
		//	Component Tokens.
		return runComponentCommand(commandTokens);
	}
	else
	{
		return false;
	}
}

//	Run the Entity Command.
bool SceneMaker::runEntityCommand(const std::vector<std::string>& currentEntityCommand)
{
	if (currentEntityCommand[1] == "#Create")
	{
		//	Create the new Entity.
		long int newEntityID = entityManager.lock()->createEntity();

		//	Add the Entity under the provided name.
		mapEntityNameToEntityID[currentEntityCommand[2]] = newEntityID;

		//	Return True.
		return true;
	}
	else if (currentEntityCommand[1] == "#Destroy")
	{
		//	Destroy the Entity under the provided name,
		entityManager.lock()->destroyEntity(mapEntityNameToEntityID[currentEntityCommand[2]]);

		//	Remove the Entity entry.
		mapEntityNameToEntityID.erase(currentEntityCommand[2]);

		//	Return True.
		return true;
	}
	else
	{
		return false;
	}
}

//	Run the Component Command.
bool SceneMaker::runComponentCommand(const std::vector<std::string>& currentComponentCommand)
{
	if (currentComponentCommand[1] == "#Add")
	{
		return addComponentCommand(currentComponentCommand);
	}
	else if (currentComponentCommand[1] == "#Update")
	{
		return updateComponentCommand(currentComponentCommand);
	}
	else if (currentComponentCommand[1] == "#Remove")
	{
		return removeComponentCommand(currentComponentCommand);
	}
	else
	{
		return false;
	}
}

//	Add the Component 
bool SceneMaker::addComponentCommand(const std::vector<std::string>& currentComponentCommand)
{
	//	Get the Entity By Name.
	long int entityID = mapEntityNameToEntityID[currentComponentCommand[2]];

	//	Get the Component Type.
	ComponentType newComponentType = getComponentType(currentComponentCommand[3]);

	//	Check if we have a valid Component Type.
	if (newComponentType != ComponentType::NO_COMPONENT)
	{
		//	Add the Component To the Entity.
		entityManager.lock()->addComponentToEntity(entityID, newComponentType);

		//	Return True.
		return true;
	}
	else
	{
		//	Return False.
		return false;
	}
}

//	Update the Component
bool SceneMaker::updateComponentCommand(const std::vector<std::string>& currentComponentCommand)
{
	//	Get the Entity By Name.
	long int entityID = mapEntityNameToEntityID[currentComponentCommand[2]];

	//	Update the Specific Type Component of the EntityID. 
	return updateSpecificTypeComponent(entityID, currentComponentCommand);
}

//	Remove the Component
bool SceneMaker::removeComponentCommand(const std::vector<std::string>& currentComponentCommand)
{
	//	Get the Entity By Name.
	long int entityID = mapEntityNameToEntityID[currentComponentCommand[2]];

	//	Get the Component Type.
	ComponentType newComponentType = getComponentType(currentComponentCommand[3]);

	//	Check if we have a valid Component Type.
	if (newComponentType != ComponentType::NO_COMPONENT)
	{
		//	Remove the Component From the Entity.
		entityManager.lock()->removeComponentFromEntity(entityID, newComponentType);

		//	Return True.
		return true;
	}
	else
	{
		//	Return False.
		return false;
	}
}

//	Return the Component Type.
ComponentType SceneMaker::getComponentType(const std::string & componentType)
{
	if (componentType == "Hierarchy")
	{
		return ComponentType::HIERARCHY_COMPONENT;
	}

	else if (componentType == "Transform")
	{
		return ComponentType::TRANSFORM_COMPONENT;
	}

	else if (componentType == "Geometry")
	{
		return ComponentType::GEOMETRY_COMPONENT;
	}

	else if (componentType == "Rendering")
	{
		return ComponentType::RENDERING_COMPONENT;
	}

	else if (componentType == "Light")
	{
		return ComponentType::LIGHT_COMPONENT;
	}

	else if (componentType == "Camera")
	{
		return ComponentType::CAMERA_COMPONENT;
	}
	else
	{
		return ComponentType::NO_COMPONENT;
	}
}

//	Update the Specific Type Component.
bool SceneMaker::updateSpecificTypeComponent(const long int & entityID, const std::vector<std::string>& currentComponentCommand)
{
	if (currentComponentCommand[3] == "Hierarchy")
	{
		return updateHierarchyTypeComponent(entityID, currentComponentCommand);
	}

	else if (currentComponentCommand[3] == "Transform")
	{
		return updateTransformTypeComponent(entityID, currentComponentCommand);
	}

	else if (currentComponentCommand[3] == "Geometry")
	{
		return updateGeometryTypeComponent(entityID, currentComponentCommand);
	}

	else if (currentComponentCommand[3] == "Rendering")
	{
		return updateRenderingTypeComponent(entityID, currentComponentCommand);
	}

	else if (currentComponentCommand[3] == "Light")
	{
		return false;
	}

	else if (currentComponentCommand[3] == "Camera")
	{
		return false;
	}
	else
	{
		return false;
	}
}

//	Update the Hierarchy Type Component.
bool SceneMaker::updateHierarchyTypeComponent(const long int & entityID, const std::vector<std::string>& currentComponentCommand)
{
	//	Get the Hierarchy Component for the Entity ID.
	std::shared_ptr<HierarchyComponent> hierarchyComponent = std::dynamic_pointer_cast<HierarchyComponent>(entityManager.lock()->getComponentOfEntity(entityID, ComponentType::HIERARCHY_COMPONENT, "NO_MODULE"));

	if (hierarchyComponent != NULL)
	{
		if (currentComponentCommand[4] == "AddChild")
		{
			long int childEntityID = mapEntityNameToEntityID[currentComponentCommand[5]];
			hierarchyComponent->addChild(childEntityID);
			return true;
		}
		else if (currentComponentCommand[4] == "RemoveChild")
		{
			long int childEntityID = mapEntityNameToEntityID[currentComponentCommand[5]];
			hierarchyComponent->removeChild(childEntityID);
			return true;
		}
		else if (currentComponentCommand[4] == "AddParent")
		{
			long int parentEntityID = mapEntityNameToEntityID[currentComponentCommand[5]];
			hierarchyComponent->setParent(parentEntityID);	
			return true;
		}
		else if (currentComponentCommand[4] == "RemoveParent")
		{
			hierarchyComponent->unParent();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//	Update the Transfomr Type Component.
bool SceneMaker::updateTransformTypeComponent(const long int & entityID, const std::vector<std::string>& currentComponentCommand)
{
	//	Get the Transform Component for the Entity ID.
	std::shared_ptr<TransformComponent> transformComponent = std::dynamic_pointer_cast<TransformComponent>(entityManager.lock()->getComponentOfEntity(entityID, ComponentType::TRANSFORM_COMPONENT, "NO_MODULE"));

	//	Check if we have a valid Transform Component.
	if (transformComponent != NULL)
	{
		
		if (currentComponentCommand[4] == "RotateBy")
		{
			glm::vec3 axes = glm::vec3(std::stof(currentComponentCommand[5]), std::stof(currentComponentCommand[6]), std::stof(currentComponentCommand[7]));

			transformComponent->getTransform()->rotateBy(std::stof(currentComponentCommand[8]), axes);

			return true;
		}
		else if (currentComponentCommand[4] == "ScaleBy")
		{
			transformComponent->getTransform()->scaleBy(glm::vec3(std::stof(currentComponentCommand[5]), std::stof(currentComponentCommand[6]), std::stof(currentComponentCommand[7])));

			return true;
		}
		else if (currentComponentCommand[4] == "TranslateBy")
		{
			transformComponent->getTransform()->translateBy(glm::vec3(std::stof(currentComponentCommand[5]), std::stof(currentComponentCommand[6]), std::stof(currentComponentCommand[7])));

			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
}

//	Update the Geometry Type Component.
bool SceneMaker::updateGeometryTypeComponent(const long int & entityID, const std::vector<std::string>& currentComponentCommand)
{
	//	Get the Geometry Component for the Entity ID.
	std::shared_ptr<GeometryComponent> geometryComponent = std::dynamic_pointer_cast<GeometryComponent>(entityManager.lock()->getComponentOfEntity(entityID, ComponentType::GEOMETRY_COMPONENT, "NO_MODULE"));

	if (geometryComponent != NULL)
	{
		geometryComponent->setGeometryType(currentComponentCommand[4]);
	
		return true;
	}
	else
	{
		return false;
	}
}

//	Update the Rendering Type Component.
bool SceneMaker::updateRenderingTypeComponent(const long int & entityID, const std::vector<std::string>& currentComponentCommand)
{
	//	Get the Rendering Component for the Entity ID.
	std::shared_ptr<RenderingComponent> renderingComponent = std::dynamic_pointer_cast<RenderingComponent>(entityManager.lock()->getComponentOfEntity(entityID, ComponentType::RENDERING_COMPONENT, "NO_MODULE"));

	if (renderingComponent != NULL)
	{
		if (currentComponentCommand[4] == "Material")
		{
			renderingComponent->setMaterialType(currentComponentCommand[5]);
		
			return true;
		}
		else if(currentComponentCommand[4] == "ShadingType")
		{
			renderingComponent->setShadingType(currentComponentCommand[5]);

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//	
bool SceneMaker::updateLightTypeComponent(const long int & entityID, const std::vector<std::string>& currentComponentCommand)
{
	//	Get the Light Component for the Entity ID.
	std::shared_ptr<LightComponent> lightComponent = std::dynamic_pointer_cast<LightComponent>(entityManager.lock()->getComponentOfEntity(entityID, ComponentType::LIGHT_COMPONENT, "NO_MODULE"));

	if (lightComponent != NULL)
	{
		if (currentComponentCommand[4] == "LightColorAndIntensity")
		{
			//	Extract the Light Color And Intensity.
			std::vector<std::string> lightColorAndIntensityValues = StringModifiers::split_string(currentComponentCommand[5], " ");
			glm::vec4 lightColorAndIntensity = glm::vec4(std::stof(lightColorAndIntensityValues[0]), std::stof(lightColorAndIntensityValues[1]), std::stof(lightColorAndIntensityValues[2]), std::stof(lightColorAndIntensityValues[3]));

			//	Set the Light Color And Intensity.
			lightComponent->setLightColorAndIntensity(lightColorAndIntensity);
		}
		else if(currentComponentCommand[4] == "LightDistanceAttenuation")
		{
			//	Extract the Light Distance Attenuation.
			std::vector<std::string> lightDistanceAttenuationValues = StringModifiers::split_string(currentComponentCommand[5], " ");
			glm::vec4 lightDistanceAttenuation = glm::vec4(std::stof(lightDistanceAttenuationValues[0]), std::stof(lightDistanceAttenuationValues[1]), std::stof(lightDistanceAttenuationValues[2]), std::stof(lightDistanceAttenuationValues[3]));

			//	Set the Light Distance Attenuation.
			lightComponent->setLightDistanceAttenuation(lightDistanceAttenuation);
		}
	}
	else
	{
		return false;
	}

	return false;
}

//	Check whether we should ignore the current line.
bool SceneMaker::shouldIgnoreLine(const std::string & line)
{
	//	Check for empty line.
	if (line == "")
		return true;

	//	Check for commented out line.
	if (line.size() >= 2)
		if (line.at(0) == '/' && line.at(1) == '/')
			return true;

	//	Add additional lines to check for and ignore.


	//	Return false if none of the ignore checks match.
	return false;
}



