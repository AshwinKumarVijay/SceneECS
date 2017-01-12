#pragma once

#include <map>
#include <string>

#include "GL\glew.h"

class RendererShaderData
{
public:

	//	Default RendererShaderData Constructor.
	RendererShaderData();

	//	Default RendererShaderData Destructor.
	virtual ~RendererShaderData();

	//	Return the Shader ID.
	unsigned int getShaderID() const;

	//	Set the Shader ID.
	virtual void setShaderID(const unsigned int & newShaderID);

	//	Return the Vertex Shader ID.
	unsigned int getVertexShaderID() const;

	//	Set the Vertex Shader ID.
	virtual void setVertexShaderID(const unsigned int & newVertexShaderID);

	//	Return the Fragment Shader ID.
	unsigned int getFragmentShaderID() const;

	//	Set the Fragment Shader ID.
	virtual void setFragmentShaderID(const unsigned int & newFragmentShaderID);

	//	Add the property value.
	virtual void addPropertyValue(const std::string & propertyType, const std::string & propertyValue);

	//	Return the Property Value associated with the Property Type.
	bool getPropertyValue(const std::string & propertyType, std::string & propertyValue) const;

	//	Add a Uniform Location with the Uniform Name.
	virtual void addUniformLocation(const std::string & uniformName, const int & uniformLocation);

	//	Return the Uniform Location with the Uniform Name. 
	bool getUniformLocation(const std::string & uniformName, int & uniformLocation) const;


private:

	//	The Shader ID.
	unsigned int shaderID;

	//	The Vertex Shader ID.
	unsigned int vsID;

	//	The Fragment Shader ID.
	unsigned int fsID;

	//	The Map of the Property to the Value.
	std::map<std::string, std::string> mapPropertyToValues;

	//	Map of the Uniform Name to the Uniform Location.
	std::map<std::string, int> mapUniformNameToUniformLocation;
};


