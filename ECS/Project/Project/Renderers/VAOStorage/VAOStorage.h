#pragma once
#include <memory>
#include <vector>
#include <map>

#include "../RenderablesMetaData.h"

struct GeometryTypeMetaData;

class VAOStorage
{

public:
	
	//	Default VAOStorage Constructor.
	VAOStorage();

	//	Default VAOStorage Destructor.
	virtual ~VAOStorage();

	//	Add the Geometry Type.
	virtual void addGeometryType(std::shared_ptr<GeometryTypeMetaData> newGeometryType);

	//	Delete the Geometry Type.
	virtual void deleteGeometryType(std::shared_ptr<GeometryTypeMetaData> deadGeometryType);


private:

	//	Return a VAO for the Geometry.
	virtual std::shared_ptr<VAOMetaData> getVAOforGeometry();

	//	The Vector of VAOs.
	std::vector<std::shared_ptr<VAOMetaData>> VAOs;

	//	The Geometry Data Type to the VAOs.
	std::multimap<unsigned int, std::shared_ptr<VAOMetaData>> mapGeometryDataTypeToVAOs;
};

