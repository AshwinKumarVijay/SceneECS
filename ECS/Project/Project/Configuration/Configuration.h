#pragma once


#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../StringModifiers/StringModifiers.h"

class Configuration
{

public:

	//	Return the configuration stored.
	static Configuration & getConfiguration();

	//	Purpose: Load the configuration in from the given file.
	virtual void loadConfigurationFromFile(const std::string & fileName);

	//	Return the property value, by writing it into the providedValue argument.
	virtual void getProperty(const std::string & propertyName, std::string & propertyValue) const;

	//	Return the property value.
	virtual std::string getProperty(const std::string & propertyName) const;

	//	Deleted functions to prevent multiple copies of the configuration.
	Configuration(Configuration const &) = delete;
	void operator=(Configuration const &) = delete;

protected:

	//	Default Configuration Constructor.
	Configuration();

	//	Default Configuration Destructor.
	virtual ~Configuration();


private:

	//	Map of Configuration Properties to the Configuration Value.
	std::map<std::string, std::string> properties;

};

