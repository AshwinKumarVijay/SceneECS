#pragma once

#include <string>
#include <map>

class ResourceDescription
{

public:
	//	Default Resource Description Constructor.
	ResourceDescription();

	//	Default Resource Description Desctructor.
	virtual ~ResourceDescription();

	//	Return the Properties, in an editiable form.
	virtual std::map<std::string, std::string> & getProperties();

	//	Return the Properties, in an non-editable form.
	virtual const std::map<std::string, std::string> & viewProperties() const;

	//	Return whether the property is available, and write it into the provided string.
	virtual bool findProperty(const std::string & propertyName, std::string & propertyValue) const;
	
private:

	std::map<std::string, std::string> properties;

};