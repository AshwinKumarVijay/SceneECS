#include "ShaderData.h"


//	Default ShaderData Constructor
ShaderData::ShaderData(const std::map<std::string, std::string> & newMapShaderPropertyToValue)
{
	//	Construct the Map from the given Map.
	properties = std::map<std::string, std::string>(newMapShaderPropertyToValue);
}

//	Default ShaderData Destructor
ShaderData::~ShaderData()
{

}

std::map<std::string, std::string>& ShaderData::getProperties()
{
	return properties;
}

const std::map<std::string, std::string>& ShaderData::viewProperties() const
{
	return properties;
}

bool ShaderData::findProperty(const std::string & propertyName, std::string & propertyValue) const
{
	//	Look for the property.
	auto itr = properties.find(propertyName);

	//	Return false if the property was not found.
	if (itr == properties.end())
	{
		return false;
	}
	else
	{
		propertyValue = itr->second;
		return true;
	}
}
