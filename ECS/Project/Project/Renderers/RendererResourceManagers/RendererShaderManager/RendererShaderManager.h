#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>

#include "GL\glew.h"


class RendererShaderData;

class RendererShaderManager
{
public:

	//	Default RendererShaderManager Constructor.
	RendererShaderManager();

	//	Default RendererShaderManager Destructor.
	virtual ~RendererShaderManager();

	//	Add a Shader to the RendererShaderManager.
	virtual void addShader(std::shared_ptr<RendererShaderData> newShaderData);

	//	Return the RendererShaderData associated with the shaderType.
	virtual std::shared_ptr<const RendererShaderData> viewShaderData(const std::string & shaderType) const;

	// Return the Shader Geometry Description Representation 
	// The Type of the Geometry = 0 - NO VERTEX INFORMATION, 1 - VERTEX BASIC DATA, 2 - VERTEX TANGENT BITANGENT DATA, 4 - VERTEX TEXTURE COORDINATES.
	virtual int getGeometryVertexRequirementsForShader(const std::string & shaderType) const;

	//	Delete the Shader with the specified name.
	virtual void deleteShader(const std::string & deadShaderType);

private:

	//	Reads the Shader source code from a file.
	GLuint readShaderStageFromFile(GLenum shaderType, const std::string & filepath);

	//	Generate the Shader Uniform Locations.
	void generateShaderUniformLocations(std::shared_ptr<RendererShaderData> newShaderData);


	//	Map the Name to the RendererShaderData.
	std::map<std::string, std::shared_ptr<RendererShaderData>> mapNameToRendererShaderData;
};

