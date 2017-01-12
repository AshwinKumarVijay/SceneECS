#pragma once
#include <string>

class SceneResourceRequest
{

public:

	//	
	SceneResourceRequest(const std::string & newRequestType, const std::string & newResourceType);

	//
	virtual ~SceneResourceRequest();

	//	
	virtual std::string getRequestType();

	//	
	virtual std::string getResourceType();


private:

	//	Request Type can be "ADD", "UPDATE", "DELETE"
	std::string requestType;

	//	Resource Type can be anything. But, of course, error if the Resource Type does not match a proper resource.
	std::string resourceType;

};

