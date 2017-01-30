#include "RendererShaderManager.h"
#include "../Resources/ResourceData/ShaderData/ShaderData.h"
#include "RendererShaderData\RendererShaderData.h"

//	Default RendererShaderManager Constructor
RendererShaderManager::RendererShaderManager()
{

}

//	Default RendererShaderManager Destructor
RendererShaderManager::~RendererShaderManager()
{

}


//	Add Shader by name.
void RendererShaderManager::addShader(std::shared_ptr<RendererShaderData> newShaderData)
{

	std::string newShaderType;
	if (!newShaderData->getPropertyValue("Shader Type", newShaderType))
	{
		throw "Error! RendererShaderManager: Add Shader -> No Shader Type!";

	}


	//	Check whether a Shader of the specified name exists.
	auto shaderi = mapNameToRendererShaderData.find(newShaderType);

	if (shaderi != mapNameToRendererShaderData.end())
	{
		//	Throw Shader Already Exists Error.
		throw "Error! RendererShaderManager: Add Shader -> Shader with Specified Name Already Exists!";
	}
	else
	{
		//	Create the Program.
		unsigned int newShaderID = glCreateProgram();
		
		if (newShaderID == 0)
		{
			throw "Error! RendererShaderManager: Add Shader -> Could not create program!";
		}
		else
		{
			newShaderData->setShaderID(newShaderID);
		}

		//	Return the Vertex Source Source.
		std::string vsSource;
		if (newShaderData->getPropertyValue("Vertex Shader Source", vsSource))
		{
			//	Read the Vertex Shader Stage from File.
			newShaderData->setVertexShaderID(readShaderStageFromFile(GL_VERTEX_SHADER, vsSource));
		}
		else
		{
			throw "Error! RendererShaderManager: Add Shader -> No Vertex Shader Source!";
		}


		//	Return the Vertex Source Source.
		std::string fsSource;
		if (newShaderData->getPropertyValue("Fragment Shader Source", fsSource))
		{
			//	Read the Vertex Shader Stage from File.
			newShaderData->setFragmentShaderID(readShaderStageFromFile(GL_FRAGMENT_SHADER, fsSource));
		}
		else
		{
			throw "Error! RendererShaderManager: Add Shader -> No Fragment Shader Source!";
		}


		//	Attach the Vertex Shader to the Shader ID.
		glAttachShader(newShaderData->getShaderID(), newShaderData->getVertexShaderID());

		//	Attach the Fragment Shader to the Shader ID.
		glAttachShader(newShaderData->getShaderID(), newShaderData->getFragmentShaderID());

		//	Link the Program together.
		glLinkProgram(newShaderData->getShaderID());

		//	Map the Name of the Shader To the RendererShaderData.
		mapNameToRendererShaderData[newShaderType] = newShaderData;

		//	
		generateShaderUniformLocations(newShaderData);
	}
}



//	View the Shader Data by name.
std::shared_ptr<const RendererShaderData> RendererShaderManager::viewShaderData(const std::string & shaderType) const
{
	//	Find the Shader specified by name.
	auto shaderi = mapNameToRendererShaderData.find(shaderType);

	//	Check if the Shader exists.
	if (shaderi != mapNameToRendererShaderData.end())
	{
		//	Return the Shader Data.
		return shaderi->second;
	}
	else
	{
		//	Throw Exception if Shader is Not Found.
		throw "Error! RendererShaderManager: View Shader Data -> Shader with Specified Name Does Not Exist!";

		//	Return NULL.
		return NULL;
	}

}

//	Return the Shader Geometry Description Requirement Representation.
int RendererShaderManager::getGeometryVertexRequirementsForShader(const std::string & shaderType) const
{
	//	Find the shader.
	auto shaderi = mapNameToRendererShaderData.find(shaderType);

	//	Check if the Shader exists.
	if (shaderi != mapNameToRendererShaderData.end())
	{
		int shaderGeometryDescriptionRepresentation = 0;

		//	Find the types of Geometry Data that the Shader Requires. Check for Vertex Basic Data.
		std::string vertexBasicDataRequirement;
		if (shaderi->second->getPropertyValue("Require Vertex Basic Data", vertexBasicDataRequirement))
		{
			if (vertexBasicDataRequirement == "True")
			{
				shaderGeometryDescriptionRepresentation = shaderGeometryDescriptionRepresentation | 1;
			}
		}


		//	Find the types of Geometry Data that the Shader Requires. Check for Vertex Tandgent and Bitangent Data.
		std::string vertexTangentBitangentRequirement;
		if (shaderi->second->getPropertyValue("Require Vertex Tangent Bitangent Data", vertexTangentBitangentRequirement))
		{
			if (vertexTangentBitangentRequirement == "True")
			{
				shaderGeometryDescriptionRepresentation = shaderGeometryDescriptionRepresentation | 2;
			}
		}

		//	Find the types of Geometry Data that the Shader Requires. Check for Vertex Texture Coordinates.
		std::string vertexTextureCoordinatesRequirement;
		if (shaderi->second->getPropertyValue("Require Vertex Texture Coordinates Data", vertexTextureCoordinatesRequirement))
		{
			if (vertexTextureCoordinatesRequirement == "True")
			{
				shaderGeometryDescriptionRepresentation = shaderGeometryDescriptionRepresentation | 4;
			}
		}

		//	
		return shaderGeometryDescriptionRepresentation;
	}
	else
	{
		//	Throw Exception if Shader is Not Found.
		throw "Error! RendererShaderManager: Get Geometry Vertex Requirements -> Shader with Specified Name Does Not Exist!";
		return 0;
	}
}

//	Delete the Shader by name.
void RendererShaderManager::deleteShader(const std::string & deadShaderType)
{
	//	Find the shader by name.
	auto shaderi = mapNameToRendererShaderData.find(deadShaderType);

	//	Check if the Shader exists.
	if (shaderi != mapNameToRendererShaderData.end())
	{
		//	Delete the Shader program.
		glDeleteProgram(shaderi->second->getShaderID());

		//	Erase the Shader.
		mapNameToRendererShaderData.erase(shaderi);
	}
	else
	{
		//	Throw Shader Does Not Exist Error.
		throw "Error! RendererShaderManager: Delete Shader -> Shader with Specified Name Does Not Exist!";
	}
}

//	Read the Shader Stage in from the file.
GLuint RendererShaderManager::readShaderStageFromFile(GLenum shaderType, const std::string & filepath)
{
	//	Initialize the Shader Reference.
	GLuint shaderReference = 0;

	//	The Shader String.
	std::string shaderFileString = "";

	//	Open the file.
	std::ifstream sourceFile(filepath, std::ifstream::in);

	//	Open the SourceFile.
	if (sourceFile.is_open())
	{
		//	Create the Shader.
		shaderReference = glCreateShader(shaderType);

		//	
		std::string line = "";

		//	Read the Shader in line by line.
		while (!sourceFile.eof())
		{
			getline(sourceFile, line);

			shaderFileString.append(line + " \n");
		}

		//	C style version of the Shader File.
		const GLchar * shaderSource = shaderFileString.c_str();

		//	Assign the Shader Source.
		glShaderSource(shaderReference, 1, (const GLchar **)& shaderSource, NULL);

		//	Compile the Shader Source.
		glCompileShader(shaderReference);

		//	Check shader for errors 
		GLint shaderCompiled = GL_FALSE;

		//	Check if the Shader has been complied.
		glGetShaderiv(shaderReference, GL_COMPILE_STATUS, &shaderCompiled);

		//	
		if (shaderCompiled != GL_TRUE)
		{
			//	Print an error if the Shader failed to complie.
			printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderReference, shaderSource);

			//	Delete the Shader.
			glDeleteShader(shaderReference);

			//	Set the Shader to be 0.
			shaderReference = 0;
		}
	}
	else
	{
		//	Mark it as unable to be open.
		printf("Unable to open shader. \n");

	}

	//	Return the Shader Reference.
	return shaderReference;
}

//	Generate the Uniform Locations for the provided shader.
void RendererShaderManager::generateShaderUniformLocations(std::shared_ptr<RendererShaderData> newShaderData)
{
	{
		//	AMBIENT LIGHT DATA, AND LIGHT ARRAY
		newShaderData->addUniformLocation("u_backgroundEnvironmentIntensities", glGetUniformLocation(newShaderData->getShaderID(), "u_environmentMapIntensities"));
		newShaderData->addUniformLocation("u_backgroundEnvironmentCubeMapOne", glGetUniformLocation(newShaderData->getShaderID(), "u_backgroundEnvironmentCubeMapOne"));
		newShaderData->addUniformLocation("u_backgroundEnvironmentCubeMapTwo", glGetUniformLocation(newShaderData->getShaderID(), "u_backgroundEnvironmentCubeMapTwo"));
		newShaderData->addUniformLocation("u_backgroundEnvironmentCubeMapThree", glGetUniformLocation(newShaderData->getShaderID(), "u_backgroundEnvironmentCubeMapThree"));
		newShaderData->addUniformLocation("u_backgroundEnvironmentCubeMapFour", glGetUniformLocation(newShaderData->getShaderID(), "u_backgroundEnvironmentCubeMapFour"));
	}

	{
		//	UNIT SQUARE AND HEMISPHERE SAMPLES.
		newShaderData->addUniformLocation("u_screenSize", glGetUniformLocation(newShaderData->getShaderID(), "u_screenSize"));
		newShaderData->addUniformLocation("u_unitSquareSamples", glGetUniformLocation(newShaderData->getShaderID(), "u_unitSquareSamples"));
		newShaderData->addUniformLocation("u_hemisphereSamples", glGetUniformLocation(newShaderData->getShaderID(), "u_hemisphereSamples"));
		newShaderData->addUniformLocation("u_hemisphereRadius", glGetUniformLocation(newShaderData->getShaderID(), "u_hemisphereRadius"));
	}

	{
		//	CAMERA DATA. UNIFORM CAMERA POSITION, CAMERA PERSPECTIVE MATRIX, CAMERA VIEW MATRIX.
		newShaderData->addUniformLocation("u_worldCameraPosition", glGetUniformLocation(newShaderData->getShaderID(), "u_worldCameraPosition"));
		newShaderData->addUniformLocation("u_cameraPerspectiveMatrix", glGetUniformLocation(newShaderData->getShaderID(), "u_cameraPerspectiveMatrix"));
		newShaderData->addUniformLocation("u_cameraViewMatrix", glGetUniformLocation(newShaderData->getShaderID(), "u_cameraViewMatrix"));
		newShaderData->addUniformLocation("u_inverseTransposeCameraViewMatrix", glGetUniformLocation(newShaderData->getShaderID(), "u_inverseTransposeCameraViewMatrix"));
		newShaderData->addUniformLocation("u_screenSpaceViewMatrix", glGetUniformLocation(newShaderData->getShaderID(), "u_screenSpaceViewMatrix"));
		newShaderData->addUniformLocation("u_cameraNearFarPlaneDistance", glGetUniformLocation(newShaderData->getShaderID(), "u_cameraNearFarPlaneDistance"));
	}

	{
		newShaderData->addUniformLocation("u_ambientLight", glGetUniformLocation(newShaderData->getShaderID(), "u_ambientLight"));
		newShaderData->addUniformLocation("u_lights", glGetUniformLocation(newShaderData->getShaderID(), "u_lights"));
	}

	{
		//	MODEL DATA. UNIFORM MODEL, INVERSE MODEL, NORMAL MATRIX.
		newShaderData->addUniformLocation("u_modelMatrix", glGetUniformLocation(newShaderData->getShaderID(), "u_modelMatrix"));
		newShaderData->addUniformLocation("u_inverseTransposeModelMatrix", glGetUniformLocation(newShaderData->getShaderID(), "u_inverseTransposeModelMatrix"));
		newShaderData->addUniformLocation("u_modelViewMatrix", glGetUniformLocation(newShaderData->getShaderID(), "u_modelViewMatrix"));
		newShaderData->addUniformLocation("u_inverseTransposeModelViewMatrix", glGetUniformLocation(newShaderData->getShaderID(), "u_inverseTransposeModelViewMatrix"));
	}

	{
		//	MATERIAL DATA. DIFFUSE ALBEDO, METALLICNESS, ROUGHNESS, FRESNEL, OPACITY.
		newShaderData->addUniformLocation("u_diffuseAlbedoAndLitType", glGetUniformLocation(newShaderData->getShaderID(), "u_diffuseAlbedoAndLitType"));
		newShaderData->addUniformLocation("u_specularAlbedoAndLightingType", glGetUniformLocation(newShaderData->getShaderID(), "u_specularAlbedoAndLightingType"));
		newShaderData->addUniformLocation("u_emssionColorAndIntensity", glGetUniformLocation(newShaderData->getShaderID(), "u_emssionColorAndIntensity"));
		newShaderData->addUniformLocation("u_metallicnessRoughnessFresnelOpacity", glGetUniformLocation(newShaderData->getShaderID(), "u_metallicnessRoughnessFresnelOpacity"));
	}

	{
		//	G BUFFER - VERTEX POSITION AND DEPTH, VERTEX NORMAL, VERTEX TEXTURE COORDINATES
		//	DIFFUSE ALBEDO AND METALLICNESS, SPECULAR ALBEDO AND ROUGHNESS, EMISSIVE COLOR AND INTENSITY.
		newShaderData->addUniformLocation("g_worldSpaceVertexPosition", glGetUniformLocation(newShaderData->getShaderID(), "g_worldSpaceVertexPosition"));
		newShaderData->addUniformLocation("g_worldSpaceVertexNormalAndDepth", glGetUniformLocation(newShaderData->getShaderID(), "g_worldSpaceVertexNormalAndDepth"));
		newShaderData->addUniformLocation("g_diffuseAlbedoAndLitType", glGetUniformLocation(newShaderData->getShaderID(), "g_diffuseAlbedoAndLitType"));
		newShaderData->addUniformLocation("g_specularAlbedoAndLightingType", glGetUniformLocation(newShaderData->getShaderID(), "g_specularAlbedoAndLightingType"));
		newShaderData->addUniformLocation("g_emissionColorAndIntensity", glGetUniformLocation(newShaderData->getShaderID(), "g_emissionColorAndIntensity"));
		newShaderData->addUniformLocation("g_metallicnessRoughnessFresnelOpacity", glGetUniformLocation(newShaderData->getShaderID(), "g_metallicnessRoughnessFresnelOpacity"));
	}

	{
		//	ENVIRONMENT MAP CUBE TEXTURE, DIFFUSE ALBEDO MAP TEXTURE, SPECULAR ALBEDO MAP TEXTURE
		//	EMISSIVE COLOR AND INTENSITY TEXTURE, METALLIC, ROUGHNESS, FRESNEL AND OPACITY TEXTURE.
		newShaderData->addUniformLocation("u_diffuseAlbedoTexture" , glGetUniformLocation(newShaderData->getShaderID(), "u_diffuseAlbedoTexture"));
		newShaderData->addUniformLocation("u_specularAlbedoMap",  glGetUniformLocation(newShaderData->getShaderID(), "u_specularAlbedoMap"));
		newShaderData->addUniformLocation("u_emssionColorAndIntensityMap", glGetUniformLocation(newShaderData->getShaderID(), "u_emssionColorAndIntensityMap"));
		newShaderData->addUniformLocation("u_metallicnessRoughnessFresnelOpacityMap", glGetUniformLocation(newShaderData->getShaderID(), "u_metallicnessRoughnessFresnelOpacityMap"));
	}

	{
		//	POST PROCESS INPUT TEXTURES.
		newShaderData->addUniformLocation("pp_inputTextureOne", glGetUniformLocation(newShaderData->getShaderID(), "pp_inputTextureOne"));
		newShaderData->addUniformLocation("pp_inputTextureTwo", glGetUniformLocation(newShaderData->getShaderID(), "pp_inputTextureTwo"));
		newShaderData->addUniformLocation("pp_inputTextureThree", glGetUniformLocation(newShaderData->getShaderID(), "pp_inputTextureThree"));
		newShaderData->addUniformLocation("pp_inputTextureFour", glGetUniformLocation(newShaderData->getShaderID(), "pp_inputTextureFour"));

		newShaderData->addUniformLocation("pp_inputTextureFive", glGetUniformLocation(newShaderData->getShaderID(), "pp_inputTextureFive"));
		newShaderData->addUniformLocation("pp_inputTextureSix", glGetUniformLocation(newShaderData->getShaderID(), "pp_inputTextureSix"));
		newShaderData->addUniformLocation("pp_inputTextureSeven", glGetUniformLocation(newShaderData->getShaderID(), "pp_inputTextureSeven"));
		newShaderData->addUniformLocation("pp_inputTextureEight", glGetUniformLocation(newShaderData->getShaderID(), "pp_inputTextureEight"));
	}

	{
		//	NOISE TEXTURES.
		newShaderData->addUniformLocation("t_noiseTextureOne", glGetUniformLocation(newShaderData->getShaderID(), "t_noiseTextureOne"));
		newShaderData->addUniformLocation("t_noiseTextureTwo",  glGetUniformLocation(newShaderData->getShaderID(), "t_noiseTextureTwo"));
		newShaderData->addUniformLocation("t_noiseTextureThree", glGetUniformLocation(newShaderData->getShaderID(), "t_noiseTextureThree"));
		newShaderData->addUniformLocation("t_noiseTextureFour", glGetUniformLocation(newShaderData->getShaderID(), "t_noiseTextureFour"));
	}
}
