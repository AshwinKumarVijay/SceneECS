#include "Configuration.h"


//	Get the configuration object.
Configuration & Configuration::getConfiguration()
{
	static Configuration configuration;
	return configuration;
}



//	Load the configuration from the provided file.
void Configuration::loadConfigurationFromFile(const std::string & fileName)
{
	std::ifstream filestream(fileName);
	std::string key;
	std::string value;

	std::string line;
	while (std::getline(filestream, line))
	{
		int location = (int) line.find("=");
		key = line.substr(0, location);
		value = line.substr(location + 1, line.length() - location);

		StringModifiers::trim(key);
		StringModifiers::trim(value);

		std::cout << "Key : " << key << std::endl;
		std::cout << "Value : " << value << std::endl;

		properties[key] = value;
	}
}


//	Return the property value, specified by the propertyName, by writing it into the propertyValue argument.
void Configuration::getProperty(const std::string & propertyName, std::string & propertyValue) const
{
	//	Find the Property.
	auto itr = properties.find(propertyName);

	//	Check if we actually have the property.
	if (itr == properties.end())
	{
		//	Return an Error string.
		propertyValue = "ERROR! Property Not Found";
	}
	else
	{
		//	Return the property.
		propertyValue = itr->second;
	}
}


//	Return the property value, specified by the propertyName.
std::string Configuration::getProperty(const std::string & propertyName) const
{
	std::string tempProperty = "ERROR! Property Not Found";
	getProperty(propertyName, tempProperty);
	return tempProperty;
}


//	Default Configuration Constructor.
Configuration::Configuration()
{
	properties["RESOLUTION WIDTH"] = std::to_string(1280);
	properties["RESOLUTION HEIGHT"] = std::to_string(720);
}


//	Default Configuration Destructor.
Configuration::~Configuration()
{

}
