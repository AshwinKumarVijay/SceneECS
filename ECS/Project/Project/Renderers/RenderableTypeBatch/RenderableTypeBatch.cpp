#include "RenderableTypeBatch.h"
#include "../Renderable/Renderable.h"


//	Default RenderableTypeBatch Constructor.
RenderableTypeBatch::RenderableTypeBatch(const RenderableType & newRenderableType) : renderableType(newRenderableType)
{
	//	Initialize the Max Buffer Size to be 0.
	maxBufferSize = 0;

	//	Initialize the transform matrix buffer to be 0.
	transformMatrixBufferID = 0;

	//	
	dirtyTransformMatrixBuffer = true;
}


//	Default RenderableTypeBatch Destructor.
RenderableTypeBatch::~RenderableTypeBatch()
{

}

//	Add the provided Renderable to the Batch.
void RenderableTypeBatch::addRenderable(std::shared_ptr<RenderableMetaData> newRenderable)
{
	//	Check if we have the correct Renderable Type.
	if (newRenderable->renderableType == renderableType)
	{
		//	Update the Renderable Entry.
		newRenderable->renderableIndex = renderableMetaDatas.size();
		
		//	Add it to the list of RenderableMetaDatas.
		renderableMetaDatas.push_back(newRenderable);

		//	Add the Transform Matrix to the list of Transform Matrices.
		renderableTransformMatrices.push_back(newRenderable->renderable->getTransformMatrix());

		//	Signal that the OpenGL Buffer no longer represents the Transforms.
		dirtyTransformMatrixBuffer = true;
	}

}

//	Remove the provided Renderable from the Batch,
void RenderableTypeBatch::removeRenderable(std::shared_ptr<RenderableMetaData> deadRenderable)
{
	//	Check if we have the correct Renderable Type.
	if (deadRenderable->renderableType == renderableType)
	{
		//	Find the index of the renderable.
		int renderableIndex = deadRenderable->renderableIndex;

		//	
		(renderableMetaDatas)[renderableIndex] = (renderableMetaDatas)[renderableMetaDatas.size() - 1];
		(renderableTransformMatrices)[renderableIndex] = (renderableTransformMatrices)[renderableTransformMatrices.size() - 1];
		(renderableMetaDatas)[renderableIndex]->renderableIndex = renderableIndex;
		//	
		renderableMetaDatas.pop_back();
		renderableTransformMatrices.pop_back();

		//	Mark the Transform Matrix Buffer as incorrect.
		dirtyTransformMatrixBuffer = true;

		deadRenderable->renderableIndex = 0;
	}
}

//	Return the vector of Transform Matrices.
const std::vector<glm::mat4>& RenderableTypeBatch::getTransformMatrices()
{
	return renderableTransformMatrices;
}

//	Return the OpenGL ID of the Transform Matrix Buffer.
unsigned int RenderableTypeBatch::getTransformMatrixBuffer()
{
	return transformMatrixBufferID;
}

//	
void RenderableTypeBatch::updateTransformMatrix(std::shared_ptr<RenderableMetaData> rendererableMetaData, const glm::mat4 & newTransformMatrix)
{
	//	
	if (rendererableMetaData->renderableType == renderableType)
	{
		//	Set the new Transform Matrix.
		rendererableMetaData->renderable->setTransformMatrix(newTransformMatrix);

		//	Update the Renderable Transform Matrix.
		renderableTransformMatrices[rendererableMetaData->renderableIndex] = newTransformMatrix;

		//	Signal that the OpenGL Buffer no longer represents the Transforms.
		dirtyTransformMatrixBuffer = true;
	}
}

//	Return whether this is a valid Renderable Type for Rendering.
bool RenderableTypeBatch::getIsValidRenderableType()
{
	return isValidRenderableType;
}

//	Set whether this is a Valid Renderable Type.
void RenderableTypeBatch::setIsValidRenderableType(const bool & renderableTypeState)
{
	isValidRenderableType = renderableTypeState;
}
