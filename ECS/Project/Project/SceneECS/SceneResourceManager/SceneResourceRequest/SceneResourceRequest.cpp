#include "SceneResourceRequest.h"



SceneResourceRequest::SceneResourceRequest(const std::string & newRequestType, const std::string & newResourceType)
{
	requestType = newRequestType;
	resourceType = newResourceType;
}


SceneResourceRequest::~SceneResourceRequest()
{
}

std::string SceneResourceRequest::getRequestType()
{
	return requestType;
}

std::string SceneResourceRequest::getResourceType()
{
	return resourceType;
}
