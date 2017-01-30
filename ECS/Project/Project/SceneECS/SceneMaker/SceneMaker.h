#pragma once
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "../../StringModifiers/StringModifiers.h"
#include "../../TypesList/ComponentTypes.h"

class EntityManager;


class SceneMaker
{

public:

	//	Default SceneMaker Constructor.
	SceneMaker(std::shared_ptr<EntityManager> newEntityManager);

	//	Default SceneMaker Destructor.
	virtual ~SceneMaker();

	//	Parse the Scene Maker.
	virtual bool loadSceneFromFile(const std::string & SDF);

private:

	//	Run the Scene Description Vector.
	virtual bool runSDV(const std::vector<std::string> & SDV);
	virtual bool runSDVCommand(const std::string & currentCommand);

	//	Run the Entity Command.
	virtual bool runEntityCommand(const std::vector<std::string> & currentEntityCommand);

	//	Run the Component Command.
	virtual bool runComponentCommand(const std::vector<std::string> & currentComponentCommand);


	//	Add the specified Component Type from parsing the Component Command.
	virtual bool addComponentCommand(const std::vector<std::string> & currentComponentCommand);

	//	Update the specified Component Type from parsing the Component Command.
	virtual bool updateComponentCommand(const std::vector<std::string> & currentComponentCommand);

	//	Remove the specified Component Type from parsing the Component Command.
	virtual bool removeComponentCommand(const std::vector<std::string> & currentComponentCommand);


	//	Return the Component Type from the Component Type string.
	virtual ComponentType getComponentType(const std::string & componentType);

	//	Find and Update the Component of the Specified Type from parsing the 
	virtual bool updateSpecificTypeComponent(const long int & entityID, const std::vector<std::string> & currentComponentCommand);

	virtual bool updateHierarchyTypeComponent(const long int & entityID, const std::vector<std::string> & currentComponentCommand);
	virtual bool updateTransformTypeComponent(const long int & entityID, const std::vector<std::string> & currentComponentCommand);
	virtual bool updateGeometryTypeComponent(const long int & entityID, const std::vector<std::string> & currentComponentCommand);
	virtual bool updateRenderingTypeComponent(const long int & entityID, const std::vector<std::string> & currentComponentCommand);
	virtual bool updateLightTypeComponent(const long int & entityID, const std::vector<std::string> & currentComponentCommand);

	//	Check if we should ignore the line in the creation of the Scene Description.
	virtual bool shouldIgnoreLine(const std::string & line);

	//	Map the Entity Name to Entity ID.
	std::map<std::string, long int> mapEntityNameToEntityID;

	//	The associated Entity Manager.
	std::weak_ptr<EntityManager> entityManager;

};

