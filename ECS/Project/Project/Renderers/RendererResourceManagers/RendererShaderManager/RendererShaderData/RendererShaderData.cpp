#include "RendererShaderData.h"



RendererShaderData::RendererShaderData()
{

}


RendererShaderData::~RendererShaderData()
{

}


//	Return the Shader ID.
unsigned int RendererShaderData::getShaderID() const
{
	return shaderID;
}

//	Set the Shader ID.
void RendererShaderData::setShaderID(const unsigned int & newShaderID)
{
	shaderID = newShaderID;
}


//	Return the Vertex Shader ID.
unsigned int RendererShaderData::getVertexShaderID() const
{
	return vsID;
}

//	Set the Vertex Shader ID.
void RendererShaderData::setVertexShaderID(const unsigned int & newVertexShaderID)
{
	vsID = newVertexShaderID;
}

//	Return the Fragment Shader ID.
unsigned int RendererShaderData::getFragmentShaderID() const
{
	return fsID;
}

//	Set the Fragment Shader ID.
void RendererShaderData::setFragmentShaderID(const unsigned int & newFragmentShaderID)
{
	fsID = newFragmentShaderID;
}

//	Add the property value.
void RendererShaderData::addPropertyValue(const std::string & propertyType, const std::string & propertyValue)
{
	auto propertyi = mapPropertyToValues.find(propertyType);

	if (propertyi != mapPropertyToValues.end())
	{
		throw "Error! RendererShaderData: Add Property Value -> Property Already Exists!";
	}
	else
	{
		mapPropertyToValues.insert(std::make_pair(propertyType, propertyValue));
	}
}

//	Return the property value from the property type.
bool RendererShaderData::getPropertyValue(const std::string & propertyType, std::string & propertyValue) const
{
	auto propertyi = mapPropertyToValues.find(propertyType);

	if (propertyi != mapPropertyToValues.end())
	{
		propertyValue = propertyi->second;
		return true;
	}
	else
	{
		return false;
	}
}

//	Add a Uniform Location with the Uniform Name.
void RendererShaderData::addUniformLocation(const std::string & uniformName, const int & uniformLocation)
{
	auto propertyi = mapUniformNameToUniformLocation.find(uniformName);

	if (propertyi != mapUniformNameToUniformLocation.end())
	{
		throw "Error! RendererShaderData: Add Uniform Location -> Uniform Already Exists!";
	}
	else
	{
		mapUniformNameToUniformLocation.insert(std::make_pair(uniformName, uniformLocation));
	}
}

//	Return the Uniform Location from the Uniform Name.
bool RendererShaderData::getUniformLocation(const std::string & uniformName, int & uniformLocation) const
{
	auto uniformi = mapUniformNameToUniformLocation.find(uniformName);

	if (uniformi != mapUniformNameToUniformLocation.end())
	{
		uniformLocation = uniformi->second;
		return true;
	}
	else
	{
		return false;
	}

}
