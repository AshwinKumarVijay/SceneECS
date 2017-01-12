#include "ShaderResourceManager.h"
#include "../../ResourceData/ShaderData/ShaderData.h"
#include "../ECS/DispatcherReceiver/EventDispatcher/EventDispatcher.h"
#include "../ECS/DispatcherReceiver/EventReceiver/EventReceiver.h"

//	Default ShaderResourceManager Constructor
ShaderResourceManager::ShaderResourceManager(std::shared_ptr<EventQueue> newEventQueue)
	: ResourceManager(newEventQueue, "SHADER_MANAGER")

{

}

//	Default ShaderResourceManager Destructor
ShaderResourceManager::~ShaderResourceManager()
{

}

//	Process the provided resource.
void ShaderResourceManager::processResource(const ResourceDescription & newResourceDescription)
{

	std::string resourceName = "None";
	std::string resourceType = "None";

	//	
	if (newResourceDescription.findProperty("Resource Type", resourceType))
	{
		if (resourceType == "OpenGL Shader")
		{
			std::shared_ptr<ShaderData> newShaderData = std::make_shared<ShaderData>(newResourceDescription.viewProperties());

			//	Get the Resource Name. Used as the Shader Name.
			newResourceDescription.findProperty("Resource Name", resourceName);

			addShader(resourceName, newShaderData);
		}
	}
	else
	{

	}
}

//	Add the ShaderData, specified by name.
void ShaderResourceManager::addShader(std::string newShaderName, std::shared_ptr<ShaderData> newShaderData)
{
	//	Find the ShaderData.
	auto shaderIterator = mapNameToShaderData.find(newShaderName);

	if (shaderIterator != mapNameToShaderData.end())
	{
		//	TO DO
		//	Throw Shader already present error.
	}
	else
	{
		//	Insert the Shader, under the appropriate name.
		mapNameToShaderData.insert(std::make_pair(newShaderName, newShaderData));
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::SHADER_RESOURCE, ResourceEventType::RESOURCE_ADDED, "SHADER_MANAGER", newShaderName, newShaderData);
		getDispatcher()->dispatchToEventQueue(newEvent);

	}
}

//	Return the ShaderData, specified by name.
std::shared_ptr<const ShaderData> ShaderResourceManager::viewShader(std::string requestedShaderData) const
{
	//	Find the ShaderData.
	auto shaderIterator = mapNameToShaderData.find(requestedShaderData);

	if (shaderIterator != mapNameToShaderData.end())
	{
		return shaderIterator->second;
	}
	else
	{
		//	TO DO
		//	Throw did not find Shader error.
		return NULL;
	}
}

//	Delete the Shader, specified by the name.
void ShaderResourceManager::deleteShader(std::string deadShaderName)
{

	//	Find the ShaderData.
	auto shaderIterator = mapNameToShaderData.find(deadShaderName);

	if (shaderIterator != mapNameToShaderData.end())
	{
		mapNameToShaderData.erase(deadShaderName);
		std::shared_ptr<ResourceEvent> newEvent = std::make_shared<ResourceEvent>(ResourceType::SHADER_RESOURCE, ResourceEventType::RESOURCE_DESTROYED, "SHADER_MANAGER", deadShaderName, nullptr);
		getDispatcher()->dispatchToEventQueue(newEvent);
	}
	else
	{
		//	TO DO
		//	Throw did not find Shader error.
	}
}
