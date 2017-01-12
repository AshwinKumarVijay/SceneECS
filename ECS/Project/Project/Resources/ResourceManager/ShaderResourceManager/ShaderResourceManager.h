#pragma once

#include <map>
#include <memory>

#include "../ResourceManager.h"

class ShaderData;

class ShaderResourceManager : public ResourceManager
{
public:

	//	Default ShaderResourceManager Constructor
	ShaderResourceManager(std::shared_ptr<EventQueue> newEventQueue);

	//	Default ShaderResourceManager Destructor
	~ShaderResourceManager();

	//	Resource Management Functions.
	virtual void processResource(const ResourceDescription & newResourceDescription);

	//	Add Comments - TO DO
	virtual void addShader(std::string newShaderName, std::shared_ptr<ShaderData> newShaderData);

	//	Add Comments - TO DO
	std::shared_ptr<const ShaderData> viewShader(std::string requestedShaderData) const;

	//	Add Comments - TO DO
	virtual void deleteShader(std::string deadShaderName);

private:
	//	Map the Name to the Shader Data.
	std::map<std::string, std::shared_ptr<ShaderData>> mapNameToShaderData;
	
};

