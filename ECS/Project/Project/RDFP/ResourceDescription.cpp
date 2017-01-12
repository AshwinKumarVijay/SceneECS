#include "ResourceDescription.h"

//	Default Resource Description Constructor.
ResourceDescription::ResourceDescription()
{

}

//	Default Resource Description Desctructor.
ResourceDescription::~ResourceDescription()
{

}

std::map<std::string, std::string>& ResourceDescription::getProperties()
{
	return properties;
}

const std::map<std::string, std::string>& ResourceDescription::viewProperties() const
{
	return properties;
}


bool ResourceDescription::findProperty(const std::string & propertyName, std::string & propertyValue) const
{
	auto itr = properties.find(propertyName);
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
