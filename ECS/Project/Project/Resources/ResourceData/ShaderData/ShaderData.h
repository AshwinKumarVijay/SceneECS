#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "../ResourceData.h"

class ShaderData : public ResourceData
{ 

public:

	//	Default ShaderData Constructor.
	ShaderData(const std::map<std::string, std::string> & newMapShaderPropertyToValue);

	//	Default ShaderData Destructor.
	virtual ~ShaderData();

	//	Return the Properties, in an editiable form.
	virtual std::map<std::string, std::string> & getProperties();

	//	Return the Properties, in an non-editable form.
	virtual const std::map<std::string, std::string> & viewProperties() const;

	//	Return whether the property is available, and write it into the provided string.
	virtual bool findProperty(const std::string & propertyName, std::string & propertyValue) const;

private:

	//	Map the Shader Property to the Shader Value;
	std::map<std::string, std::string> properties;
};

