#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "GL\glew.h"
#include "glm\glm.hpp"

class Renderable;

struct RenderableType;
struct RenderableMetaData;
class RenderableTypeBatch;
struct RenderableTypeBatchMetaData;

struct ShaderTypeMetaData;
struct GeometryTypeMetaData;
struct MaterialTypeMetaData;

struct RendererGeometryData;
struct VAOMetaData;

//	Description of a specific Type of Renderables.
struct RenderableType
{
	//	Construct a Type given the Shader Type, the Geometry Type and the Material Type.
	RenderableType(const std::string & newShaderType, const std::string & newGeometryType, const std::string & newMaterialType)
	{
		//	The Shader Type.
		shaderType = newShaderType;

		//	The Geometry Type.
		geometryType = newGeometryType;

		//	The Material Type.
		materialType = newMaterialType;
	}

	//	Construct a Renderable Type.
	RenderableType(const RenderableType & other)
	{
		//	The Shader Type.
		shaderType = other.shaderType;

		//	The Geometry Type.
		geometryType = other.geometryType;

		//	The Material Type.
		materialType = other.materialType;
	}

	//	Overloaded Less Than Comparison Operator.
	bool operator< (const RenderableType & other) const
	{
		//	Compare the Shader Types first.
		if (shaderType < other.shaderType)
		{
			//	If the ShaderType is less than the other ShaderType.
			return true;
		}
		else if (shaderType == other.shaderType)
		{
			//	If the Shader Types are the same, compare the Geometry Types.
			if (geometryType < other.geometryType)
			{
				//	If the GeometryType is less than the other GeometryType.
				return true;
			}
			else if (geometryType == other.geometryType)
			{
				//	If the Shader Types and the Geometry Types are equal, then compare the material types.
				if (materialType < other.materialType)
				{
					//	If the MaterialType is less than the other MaterialType.
					return true;
				}
				else if (materialType == other.materialType)
				{
					//	If the ShaderType, the GeometryType and the MaterialTypes are all the same.
					return false;
				}
				else
				{
					//	If the MaterialType is greater than the other MaterialType.
					return false;
				}
			}
			else
			{
				//	If the GeometryType is greater than the other GeometryType.
				return false;
			}
		}
		else
		{
			//	If the ShaderType is greater than the other ShaderType.
			return false;
		}
	}

	//	Overaloaded Equals To Comparison Operator.
	bool operator==(const RenderableType & other) const
	{
		if (shaderType == other.shaderType && geometryType == other.geometryType && materialType == other.materialType)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//	The Shader Type.
	std::string shaderType;

	//	The Geometry Type.
	std::string geometryType;

	//	The Material Type.
	std::string materialType;
};


//	VAO Meta Data.
struct VAOMetaData
{
	//	The VAO ID.
	unsigned int vaoID = 0;

	//	The Geometry Type Meta Datas associated.
	std::map<std::string, std::shared_ptr<GeometryTypeMetaData>> geometryTypeMetaDatas;
};


//	Shader Type Meta Data
struct ShaderTypeMetaData
{
	ShaderTypeMetaData(const std::string & newShaderType)
	{
		shaderType = newShaderType;
	}

	std::string shaderType = "#NO_SHADER_TYPE";
};

//	Geometry Type Meta Data.
struct GeometryTypeMetaData
{
	GeometryTypeMetaData(const std::string & newGeometryType)
	{
		geometryType = newGeometryType;
	}

	//	Comparing Meta Data is Simply Comparing VaoIDs first, and then comparing strings.
	bool operator< (const GeometryTypeMetaData & other) const
	{
		auto vaoMD = vaoMetaData.lock();
		auto othervaoMD = other.vaoMetaData.lock();

		if (vaoMD == NULL && othervaoMD == NULL)
		{
			return false;
		}
		else if (vaoMD != NULL && othervaoMD == NULL)
		{
			return false;
		}
		else if (vaoMD == NULL && othervaoMD != NULL)
		{
			return true;
		}
		else
		{
			if (vaoMetaData.lock()->vaoID < other.vaoMetaData.lock()->vaoID)
			{
				return true;
			}
			else if (vaoMetaData.lock()->vaoID == other.vaoMetaData.lock()->vaoID)
			{
				if (geometryType < other.geometryType)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

	}

	//	Name of the Geometry Type we represent.
	std::string geometryType = "#NO_GEOMETRY_TYPE";

	//	The EBO and the offset into the EBO.
	unsigned int EBO = 0;
	unsigned int offsetEBO = 0;

	//	The vertexVBO and the offset into the vertexVBO.
	unsigned int vertexVBO = 0;
	unsigned int offsetVertexVBO = 0;

	//	The vertexNormalVBO and the offset into the vertexNormalVBO.
	unsigned int vertexNormalVBO = 0;
	unsigned int offsetVertexNormalVBO = 0;

	//	The vertexTextureVBO and the offset into the vertexVBO.
	unsigned int vertexTextureVBO = 0;
	unsigned int offsetVertexTextureVBO = 0;

	//	Weak Pointer to the Associated VAO Meta Data.
	std::weak_ptr<VAOMetaData> vaoMetaData;

	//	Shared Pointer to the Renderer Geometry Data.
	std::shared_ptr<RendererGeometryData> rendererGeometryData;
};

//	The Material Type Meta Data.
struct MaterialTypeMetaData
{
	MaterialTypeMetaData(const std::string & newMaterialType)
	{
		materialType = newMaterialType;
	}

	std::string materialType = "#NO_MATERIAL_TYPE";
};

//	Description of a specific Type Batch, with the associated data.
struct RenderableTypeBatchMetaData
{
	//	Construct a Type given the Shader Type, the Geometry Type and the Material Type.
	RenderableTypeBatchMetaData(const std::string & newShaderType, const std::string & newGeometryType, const std::string & newMaterialType) : renderableType(newShaderType, newGeometryType, newMaterialType)
	{

	}

	RenderableTypeBatchMetaData(const RenderableType & newRenderableType) : renderableType(newRenderableType)
	{
	
	}

	RenderableTypeBatchMetaData(const RenderableTypeBatchMetaData & other) : renderableType(other.renderableType.shaderType, other.renderableType.geometryType, other.renderableType.materialType)
	{
		shaderTypeMetaData = other.shaderTypeMetaData;
		geometryTypeMetaData = other.geometryTypeMetaData;
		materialTypeMetaData = other.materialTypeMetaData;
		renderableTypeBatch = other.renderableTypeBatch;
	}

	//	Compare Two Renderable Tpye Batch Meta Datas.
	bool operator < (const RenderableTypeBatchMetaData & other) const
	{
		//	Compare Shader Types.
		if (renderableType.shaderType < other.renderableType.shaderType)
		{
			return true;
		}
		else if(renderableType.shaderType > other.renderableType.shaderType)
		{
			return false;
		}
		else
		{	
			//	Shader Types are the same.
			//	Compare by Geometry Type Meta Data. (Specifically, sort by VAO ID.)
			if (geometryTypeMetaData == NULL && other.geometryTypeMetaData == NULL)
			{
				//	Compare Geometry Types if both of them are NULL.
				if (renderableType.geometryType < other.renderableType.geometryType)
				{
					return true;
				}
				else if (renderableType.geometryType > other.renderableType.geometryType)
				{
					return false;
				}
				else
				{
					//	Geometry Types are equal, then compare Material Types.
					if (renderableType.materialType < other.renderableType.materialType)
					{
						return true;
					}
					else if (renderableType.materialType > other.renderableType.materialType)
					{
						return false;
					}
					else
					{
						return false;
					}

				}
			}
			else if(geometryTypeMetaData == NULL && other.geometryTypeMetaData != NULL)
			{
				return true;
			}
			else if(geometryTypeMetaData != NULL && other.geometryTypeMetaData == NULL)
			{
				return false;
			}
			else
			{
				//	Compare VAO IDs first, if Geometry Meta Datas are not NULL.
				if (geometryTypeMetaData->vaoMetaData.lock()->vaoID < other.geometryTypeMetaData->vaoMetaData.lock()->vaoID)
				{
					return true;
				}
				else if (geometryTypeMetaData->vaoMetaData.lock()->vaoID > other.geometryTypeMetaData->vaoMetaData.lock()->vaoID)
				{
					return false;
				}
				else
				{
					//	VAO IDs are the same.
					//	Then compare Geometry Types.
					if (renderableType.geometryType < other.renderableType.geometryType)
					{
						return true;
					}
					else if (renderableType.geometryType > other.renderableType.geometryType)
					{
						return false;
					}
					else
					{
						//	Geometry Types are equal, then compare Material Types.
						if (renderableType.materialType < other.renderableType.materialType)
						{
							return true;
						}
						else if (renderableType.materialType > other.renderableType.materialType)
						{
							return false;
						}
						else
						{
							return false;
						}

					}
				}				
			}
		}
	}

	//	The Renderable Type.
	RenderableType renderableType;

	//	The Shader Type Meta Data.
	std::shared_ptr<ShaderTypeMetaData> shaderTypeMetaData = NULL;

	//	The Geometry Type Meta Data.
	std::shared_ptr<GeometryTypeMetaData> geometryTypeMetaData = NULL;
	
	//	The Material Type Meta Data.
	std::shared_ptr<MaterialTypeMetaData> materialTypeMetaData = NULL;

	//	The Renderable Type Batch.
	std::shared_ptr<RenderableTypeBatch> renderableTypeBatch = NULL;
};

//	RenderableMetaData.
struct RenderableMetaData
{
	//	Construct a Type given the Shader Type, the Geometry Type and the Material Type.
	RenderableMetaData(const std::string & newShaderType, const std::string & newGeometryType, const std::string & newMaterialType) 
		: renderableType(newShaderType, newGeometryType, newMaterialType)
	{

	}
	
	//	Renderable Index.
	unsigned int renderableIndex = 0;

	//	Renderable Type.
	RenderableType renderableType;

	//	Associated Renderable.
	std::shared_ptr<Renderable> renderable = NULL;

	//	Associated Renderable Batch.
	std::weak_ptr<RenderableTypeBatch> renderableTypeBatch = std::weak_ptr<RenderableTypeBatch>();
};


//	VAOID to Geometry Type Key.
struct VAOIDGeometryTypeKey
{
	//	Comparison for the 
	bool operator<(const VAOIDGeometryTypeKey& other) const
	{
		if (vaoID < other.vaoID)
		{
			return true;
		}
		else if (vaoID == other.vaoID)
		{
			if (geometryType < other.geometryType)
			{
				return true;
			}
			else if (geometryType == other.geometryType)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

	}

	//	The VAO ID of this Key.
	unsigned int vaoID = 0;

	//	The Geometry Type of this Key.
	std::string geometryType;
};
