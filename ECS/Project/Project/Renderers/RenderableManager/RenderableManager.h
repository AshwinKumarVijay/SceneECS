#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "GL\glew.h"
#include "glm\glm.hpp"

#include "../RenderablesMetaData.h"
#include "../RenderableTypeBatch/RenderableTypeBatch.h"
#include "../VAOStorage/VAOStorage.h"

class Renderable;
class ShaderTypeBatch;

class RenderableManager
{

public:

	//	Default RenderableManager Constructor.
	RenderableManager();

	//	Default RenderableManager Destructor.
	virtual ~RenderableManager();

	//	Create a Renderable and return the ID.
	virtual long int createRenderable();

	//	Return the const Renderable associated with the specified RenderableID
	virtual std::shared_ptr<const Renderable> viewRenderable(const long int & currentRenderableID) const;

	//	Return the Renderable associated with the RenderableID.
	virtual std::shared_ptr<Renderable> getRenderable(const long int & currentRenderableID);

	//	Return the Renderable associated with the RenderableID.
	virtual std::shared_ptr<RenderableMetaData> getRenderableMetaData(const long int & currentRenderableID);

	//	Return the Map of the RenderableID to the RenderableMetaData
	const std::map<long int, std::shared_ptr<RenderableMetaData>> & getMapOfRenderableIDToRenderableMetaData() const;

	//	Return the Map of the RenderableType to the RenderableTypeBatch.
	const std::map<RenderableType, std::shared_ptr<RenderableTypeBatch>> & getRenderableTypeBatches() const;

	//	Return the Renderable Type Batch Meta Datas.
	const std::set<RenderableTypeBatchMetaData> & getRenderableTypeBatchMetaDatas() const;

	//	Update the Shading Type associated with the specified Renderable ID.
	virtual void updateShadingType(const long int & currentRenderableID, const std::string & newShadingType);

	//	Update the Geometry Type associated with the specified Renderable ID.
	virtual void updateGeometryType(const long int & currentRenderableID, const std::string & newGeometryType);

	//	Update the Material Type associated with the specified Renderable ID.
	virtual void updateMaterialType(const long int & currentRenderableID, const std::string & newMaterialType);

	//	Update the Transform Matrix associated with the specified Renderable ID.
	virtual void updateTransformMatrix(const long int & currentRenderableID, const glm::mat4 & newTransformMatrix);

	//	Remove the Renderable specified by the Renderable ID.
	virtual void removeRenderable(const long int & deadRenderable);

	//	Add the Geometry Type.
	virtual void addGeometryType(std::shared_ptr<RendererGeometryData> newGeometryType);

	//	Update the Geometry Type.
	virtual void updateGeometryType(std::shared_ptr<RendererGeometryData> updatedGeometryData);

	//	Remove the Geometry Type.
	virtual void removeGeometryType(std::shared_ptr<RendererGeometryData> deadGeometryType);

	//	Add the Shader Type.
	virtual void addShaderType(std::string newShaderType);

	//	Remove the Shader Type.
	virtual void removeShaderType(std::string deadShaderType);

	//	Add the Material Type.
	virtual void addMaterialType(std::string newMaterialType);

	//	Remove the Material Type.
	virtual void removeMaterialType(std::string deadMaterialType);


private:

	//	Add Renderable Meta Data.
	virtual void addRenderableMetaData(std::shared_ptr<RenderableMetaData> newRenderableMetaData);

	//	Remove Renderable Meta Data.
	virtual void removeRenderableMetaData(std::shared_ptr<RenderableMetaData> deadRenderableMetaData);

	//	Update the Renderable Type Batches.
	virtual void updateRenderableTypeBatchesWithShaderType(const std::string & shaderType, bool available);
	virtual void updateRenderableTypeBatchesWithGeometryType(const std::string & shaderType, bool available);
	virtual void updateRenderableTypeBatchesWithMaterialType(const std::string & shaderType, bool available);

	//	Get the Renderable Type Batch.
	virtual std::shared_ptr<RenderableTypeBatch> getRenderableTypeBatch(const RenderableType & renderableType);

	//	Return the Geometry Type Meta Data.
	virtual std::shared_ptr<GeometryTypeMetaData> getGeometryTypeMetaData(const std::string & givenGeometryType);

	//	Check if the Shader Type is an Available Shader Type.
	virtual bool isAvailableShaderType(const std::string & givenShaderType);

	//	Check if the Geometry Type is an Available Geometry Type.
	virtual bool isAvailableGeometryType(const std::string & givenGeometryType);

	//	Check if the Material Type is an Available Material Type.
	virtual bool isAvailableMaterialType(const std::string & givenMaterialType);

	//	The Shader Types.
	std::set<std::string> shaderTypes;

	//	The Geometry Types.
	std::set<std::string> geometryTypes;

	//	The Material Types.
	std::set<std::string> materialTypes;

	//	Map the RenderableID to the Renderable Meta Data.
	std::map<long int, std::shared_ptr<RenderableMetaData>> mapRenderableIDToRenderableMetaData;

	//	The Vector of the Renderable Type Batches.
	std::map<RenderableType, std::shared_ptr<RenderableTypeBatch>> mapRenderableTypeToRenderableTypeBatches;

	//	The ordered list of Renderable Type Batch Meta Data.
	std::set<RenderableTypeBatchMetaData> renderableTypeBatchMetaDatas;

	//	Map the Geometry Type to the Geometry Type Meta Data.
	std::map<std::string, std::shared_ptr<GeometryTypeMetaData>> mapGeometryTypeToGeometryTypeMetaData;

	//	The list of Active renderable IDs.
	std::vector<long int> activeRenderables;

	//	The list of Inactive renderable IDs.
	std::vector<long int> inactiveRenderables;

	//	The VAOStorage.
	VAOStorage vaoStorage;

	//	The default initialization values for the Shader, Geometry and Material Types.
	std::string defaultShaderType;
	std::string defaultGeometryType;
	std::string defaultMaterialType;

	
};

