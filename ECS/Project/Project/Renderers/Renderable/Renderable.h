#pragma once

#include <string>
#include <vector>
#include <memory>

#include "glm\glm.hpp"

class Renderable
{

public:

	//	Default Renderable Constructor.
	Renderable(const long int & newRenderableID);

	//	Default Renderable Destructor.
	virtual ~Renderable();

	//	Return the RenderableID.
	virtual long int getRenderableID() const;

	//	Activate the Renderable.
	void activate();
	//	Return whether the Renderable is active.
	bool getActive() const;

	//	Deactivate the Renderable.
	void deactivate();
		//	Return whether the Renderable is inactive.
	bool getInactive() const;


	//	Set the Geometry Type.
	virtual void setGeometryType(const std::string & newGeometryType);
	//	Return the Geometry Type.
	virtual std::string getGeometryType() const;

	//	Set the Material Type
	virtual void setMaterialType(const std::string & newMaterialType);
	//	Get the Material Type.
	virtual std::string getMaterialType() const;

	//	Set the Shading Type.
	virtual void setShaderType(const std::string & newShaderType);
	//	Get the Shading Type.
	virtual std::string getShaderType() const;

	//	Get the Transform Matrix.
	virtual glm::mat4 getTransformMatrix() const;
	//	Set the Transform Matrix.
	virtual void setTransformMatrix(const glm::mat4 & newModelMatrix);


private:

	//	The Name of the Geometry associated with this Renderable.
	std::string geometryType;

	//	The Name of the Material associated with this Renderable.
	std::string materialType;

	//	The ShadingType associated with this Renderable.
	std::string shaderType;

	//	The Transform Matrix associated with this Renderable.
	glm::mat4 transformMatrix;

	//	The Renderable ID.
	long int renderableID;

	//	The Active Flag.
	bool activeFlag;

};

