#pragma once

#include <string>
#include <memory>
#include <vector>

#include "glm\glm.hpp"
#include "../RenderablesMetaData.h"

struct RenderableMetaData;

class RenderableTypeBatch
{
public:
	
	//	Default RenderableTypeBatch Constructor.
	RenderableTypeBatch(const RenderableType & newRenderableType);

	//	Default RenderableTypeBatch Destructor.
	virtual ~RenderableTypeBatch();

	//	Add the Renderable to the RenderableTypeBatch.
	virtual void addRenderable(std::shared_ptr<RenderableMetaData> newRenderable);

	//	Remove the Renderable from the RenderableTypeBatch.
	virtual void removeRenderable(std::shared_ptr<RenderableMetaData> deadRenderable);

	//	Returm the vector Transform Matrices.
	const std::vector<glm::mat4> & getTransformMatrices();

	//	Return the OpenGL ID for the Transform Matrix Buffer.
	unsigned int getTransformMatrixBuffer();

	//	Update the Transform Matrix of the specified renderable.
	virtual void updateTransformMatrix(std::shared_ptr<RenderableMetaData> rendererableMetaData, const glm::mat4 & newTransformMatrix);

	//	Return whether this RenderableTypeBatch is a Valid Renderable Type.
	bool getIsValidRenderableType();

	//	Set whether this RenderableTypeBatch is a Valid Renderable Type.
	virtual void setIsValidRenderableType(const bool & newRenderableState);

private:
	
	//	The Renderable Type.
	RenderableType renderableType;

	//	Whether this is a Valid Renderable Type.
	bool isValidRenderableType;

	//	The Vector of Renderable Transform Matrices.
	std::vector<glm::mat4> renderableTransformMatrices;

	//	The Vector of Renderable Meta Data.
	std::vector<std::shared_ptr<RenderableMetaData>> renderableMetaDatas;

	//	Transform Buffer State.
	unsigned int transformMatrixBufferID;
	unsigned int maxBufferSize;
	bool dirtyTransformMatrixBuffer;
};
