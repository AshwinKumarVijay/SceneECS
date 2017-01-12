#pragma once
#include <map>
#include <string>


//	The Renderer Module Shader Source.
struct RendererModuleShaderSource
{
	//	Vertex Shader Source.
	std::string vsSource;

	//	Fragment Shader Source.
	std::string fsSource;
};


//	The Renderer Module Shader MetaData.
struct RendererModuleShaderMetaData
{
	//	The Shader ID.
	unsigned int shaderID;

	//	Map the Uniform Name to Uniform Location.
	std::map<std::string, int> mapUniformNameToUniformLocation;

};