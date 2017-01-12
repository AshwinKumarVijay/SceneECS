#include "SceneOBJResourceManager.h"
#include "../SceneGeometryResourceManager/SceneGeometryResourceManager.h"
#include "../SceneMaterialResourceManager/SceneMaterialResourceManager.h"
#include "../../../Resources/ResourceData/GeometryData/GeometryData.h"
#include "TinyObjLoader\tiny_obj_loader.h"
#include "../../../Resources/ResourceData/MaterialData/MaterialData.h"

//	Default SceneOBJResouceManager Constructor.
SceneOBJResourceManager::SceneOBJResourceManager(std::shared_ptr<SceneResourceManager> newSceneResouceManager, std::shared_ptr<SceneGeometryResourceManager> newSceneGeometryResourceManager, std::shared_ptr<SceneMaterialResourceManager> newSceneMaterialResourceManager, std::shared_ptr<SceneTextureResourceManager> newSceneTextureResourceManager)
{
	//	Get the Scene Resource Manager.
	sceneResourceManager = newSceneResouceManager;

	//	Get the Scene Geometry Resource Manager to send the geometry data to,
	sceneGeometryResourceManager = newSceneGeometryResourceManager;
	
	//	Get the Scene Material Resource Manager to send the material data to.
	sceneMaterialResourceManager = newSceneMaterialResourceManager;
}

//	Default SceneOBJResouceManager Destructor.
SceneOBJResourceManager::~SceneOBJResourceManager()
{

}

//	
void SceneOBJResourceManager::loadResource(const ResourceDescription & newResourceDescription)
{
	std::string resourceName = "None";
	std::string resourceType = "None";
	std::string objSourceFileName = "None";
	std::string directory = "None";

	if (newResourceDescription.findProperty("Resource Type", resourceType))
	{
		if (resourceType == "OBJ")
		{
			if (newResourceDescription.findProperty("Resource Name", resourceName) && newResourceDescription.findProperty("Source Filename", objSourceFileName) && newResourceDescription.findProperty("Directory", directory))
			{

				//	The Vector of Generated Geometry and the Associated Geometry Data.
				std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>> newGeometryDatas;

				//	The Vector of Generated Materials, and the Associated Geometry Data.
				std::vector<std::pair<std::string, std::shared_ptr<MaterialData>>> newMaterialDatas;

				//	Load the Geometry and Material Data.
				loadObj(directory, objSourceFileName, resourceName, newGeometryDatas, newMaterialDatas);
				
				//	Insert the Geometry Data into the Geometry Manager.
				for (int i = 0; i < newGeometryDatas.size(); i++)
				{
					sceneGeometryResourceManager->addGeometry(newGeometryDatas[i].first, newGeometryDatas[i].second);
				}

				//	Insert the Material Data into the Material Manager.
				for (int i = 0; i < newMaterialDatas.size(); i++)
				{
					sceneMaterialResourceManager->addMaterial(newMaterialDatas[i].first, newMaterialDatas[i].second);
				}

			}
		}
	}
}

//	Load the Resource Requested.
void SceneOBJResourceManager::processRequest(std::shared_ptr<SceneResourceRequest> newResourceRequest)
{

}
	

//	Load the Obj File.
void SceneOBJResourceManager::loadObj(const std::string & objDirectory, const std::string & sourceFilename, const std::string & baseModelName, std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>>& newGeometryList)
{
		//	Use the tiny object loader.

		//	The attributes.
		tinyobj::attrib_t attrib;

		//	The shapes of the object.
		std::vector<tinyobj::shape_t> shapes;

		//	The materials of the object.
		std::vector<tinyobj::material_t> materials;

		//	The error string.
		std::string err;

		//	Load the Obj into the attribute, the shapes and the materials.
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, (objDirectory + sourceFilename).c_str());

		//	Check if there is any error.
		if (!err.empty())
		{
			// `err` may contain warning message.
			std::cerr << err << std::endl;
		}

		//	Quit if there was a problem with loading the object.
		if (!ret)
		{
			exit(1);
		}

		std::cout << "# of shapes    : " << shapes.size() << std::endl;
		std::cout << "# of materials : " << materials.size() << std::endl;

		//	Check if we have an Empty Material. Clear the Materials Array if we do.
		if (materials.size() == 1)
		{
			if (materials[0].name == "")
			{
				materials.clear();
			}
		}

		//	Initialize to max to zero and min to infinite.
		glm::vec3 maxXYZ = glm::vec3(0.0);
		glm::vec3 minXYZ = glm::vec3(FP_INFINITE);


		//	The list of of lists of indices.
		std::vector<std::vector<int>> currentIndicesArrays;

		//	The list of of lists of vertices.
		std::vector<std::vector<Vertex>> currentVertexArrays;

		//	Iterate over the shapes.
		for (size_t s = 0; s < shapes.size(); s++)
		{
			//	The list of Indices.
			std::vector<int> currentIndicesArray;

			//	The list of Vertices.
			std::vector<Vertex> currentVertexArray;

			//	The list of offsets.
			std::vector<glm::vec3> offsets;

			//	Create the offsets to zero the shape to the origin.
			for (size_t i = 0; i < shapes[s].mesh.indices.size(); i++)
			{
				//	Get the index of the current vertex.
				int currentVertexIndex = shapes[s].mesh.indices[i].vertex_index;

				//	Get the vertex details.
				float vx = attrib.vertices[3 * currentVertexIndex + 0];
				float vy = attrib.vertices[3 * currentVertexIndex + 1];
				float vz = attrib.vertices[3 * currentVertexIndex + 2];

				//	Create the position.
				glm::vec3 position = glm::vec3(vx, vy, vz);

				//	Compare the extremities to the position.
				if (maxXYZ.x < position.x) maxXYZ.x = position.x;
				if (maxXYZ.y < position.y) maxXYZ.y = position.y;
				if (maxXYZ.z < position.z) maxXYZ.z = position.z;

				if (minXYZ.x > position.x) minXYZ.x = position.x;
				if (minXYZ.y > position.y) minXYZ.y = position.y;
				if (minXYZ.z > position.z) minXYZ.z = position.z;

				//	Add the offset to the list of offsets. 
				offsets.push_back(position);
			}


			//	Iterate over the indices.
			for (size_t i = 0; i < shapes[s].mesh.indices.size(); i++)
			{
				//	Create a new VertexData.
				Vertex vertexData;

				//	Add it to the list of indices. 
				currentIndicesArray.push_back((int)i);

				//	Get the vertex index.
				int currentVertexIndex = shapes[s].mesh.indices[i].vertex_index;

				//	Create the position vector.
				float vx = attrib.vertices[3 * currentVertexIndex + 0];
				float vy = attrib.vertices[3 * currentVertexIndex + 1];
				float vz = attrib.vertices[3 * currentVertexIndex + 2];

				//	
				glm::vec3 position = glm::vec3(vx, vy, vz);
				vertexData.position = glm::vec4(position + offsets[i], 1.0);

				//	Get the normal vertex.
				int currentNormalIndex = shapes[s].mesh.indices[i].normal_index;

				//	Create the normal vector.
				float nx = attrib.normals[3 * currentNormalIndex + 0];
				float ny = attrib.normals[3 * currentNormalIndex + 1];
				float nz = attrib.normals[3 * currentNormalIndex + 2];

				glm::vec3 normal = glm::vec3(nx, ny, nz);
				vertexData.normal = normal;

				//	Get the texture index.
				int currentTextureIndex = shapes[s].mesh.indices[i].texcoord_index;

				currentVertexArray.push_back(vertexData);
			}

			//	Add this list of indices to the list of lists of indices.
			currentIndicesArrays.push_back(currentIndicesArray);

			//	Add this list of vertices to the list of lists of vertices.
			currentVertexArrays.push_back(currentVertexArray);
		}



		if (currentIndicesArrays.size() == 1)
		{
			//	Create the geometry data of this pair of indices and vertices.
			newGeometryList.push_back(std::make_pair(baseModelName, std::make_shared<GeometryData>(GL_TRIANGLES, currentIndicesArrays[0], currentVertexArrays[0])));
		}
		else
		{
			//	Iterate over the list of lists of indices.	
			for (int i = 0; i < currentIndicesArrays.size(); i++)
			{
				//	Create the geometry data of this pair of indices and vertices.
				std::shared_ptr<GeometryData> newGeometryDataElement = std::make_shared<GeometryData>(GL_TRIANGLES, currentIndicesArrays[i], currentVertexArrays[i]);
				newGeometryList.push_back(std::make_pair(baseModelName + std::to_string(i), newGeometryDataElement));
			}
		}
}

//	Load the OBJ file with the Materials.
void SceneOBJResourceManager::loadObj(const std::string & objDirectory, const std::string & sourceFilename, const std::string & baseModelName, std::vector<std::pair<std::string, std::shared_ptr<GeometryData>>>& newGeometryList, std::vector<std::pair<std::string, std::shared_ptr<MaterialData>>>& newMaterialsList)
{
	//	Use the tiny object loader.

	//	The attributes.
	tinyobj::attrib_t attrib;

	//	The shapes of the object.
	std::vector<tinyobj::shape_t> shapes;

	//	The materials of the object.
	std::vector<tinyobj::material_t> materials;

	//	The error string.
	std::string err;

	//	Load the Obj into the attribute, the shapes and the materials.
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, (objDirectory + sourceFilename).c_str(), objDirectory.c_str());

	//	Check if there is any error.
	if (!err.empty())
	{
		// `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	//	Quit if there was a problem with loading the object.
	if (!ret)
	{
		exit(1);
	}


	//	Check if we have an Empty Material. Clear the Materials Array if we do.
	if (materials.size() == 1)
	{
		if (materials[0].name == "")
		{
			materials.clear();
		}
	}

	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	
	std::cout << "# of materials : " << materials.size() << std::endl;


	//	Initialize to max to zero and min to infinite.
	glm::vec3 maxXYZ = glm::vec3(0.0);
	glm::vec3 minXYZ = glm::vec3(FP_INFINITE);


	//	The list of of lists of indices.
	std::vector<std::vector<int>> currentIndicesArrays;

	//	The list of of lists of vertices.
	std::vector<std::vector<Vertex>> currentVertexArrays;

	//	Iterate over the shapes.
	for (size_t s = 0; s < shapes.size(); s++)
	{
		//	The list of Indices.
		std::vector<int> currentIndicesArray;

		//	The list of Vertices.
		std::vector<Vertex> currentVertexArray;

		//	The list of offsets.
		std::vector<glm::vec3> offsets;

		//	Create the offsets to zero the shape to the origin.
		for (size_t i = 0; i < shapes[s].mesh.indices.size(); i++)
		{
			//	Get the index of the current vertex.
			int currentVertexIndex = shapes[s].mesh.indices[i].vertex_index;

			//	Get the vertex details.
			float vx = attrib.vertices[3 * currentVertexIndex + 0];
			float vy = attrib.vertices[3 * currentVertexIndex + 1];
			float vz = attrib.vertices[3 * currentVertexIndex + 2];

			//	Create the position.
			glm::vec3 position = glm::vec3(vx, vy, vz);

			//	Compare the extremities to the position.
			if (maxXYZ.x < position.x) maxXYZ.x = position.x;
			if (maxXYZ.y < position.y) maxXYZ.y = position.y;
			if (maxXYZ.z < position.z) maxXYZ.z = position.z;

			if (minXYZ.x > position.x) minXYZ.x = position.x;
			if (minXYZ.y > position.y) minXYZ.y = position.y;
			if (minXYZ.z > position.z) minXYZ.z = position.z;

			//	Add the offset to the list of offsets. 
			offsets.push_back(position);
		}


		//	Iterate over the indices.
		for (size_t i = 0; i < shapes[s].mesh.indices.size(); i++)
		{
			//	Create a new VertexData.
			Vertex vertexData;

			//	Add it to the list of indices. 
			currentIndicesArray.push_back((int)i);

			//	Get the vertex index.
			int currentVertexIndex = shapes[s].mesh.indices[i].vertex_index;

			//	Create the position vector.
			float vx = attrib.vertices[3 * currentVertexIndex + 0];
			float vy = attrib.vertices[3 * currentVertexIndex + 1];
			float vz = attrib.vertices[3 * currentVertexIndex + 2];

			//	
			glm::vec3 position = glm::vec3(vx, vy, vz);
			vertexData.position = glm::vec4(position + offsets[i], 1.0);

			//	Get the normal vertex.
			int currentNormalIndex = shapes[s].mesh.indices[i].normal_index;

			//	Create the normal vector.
			float nx = attrib.normals[3 * currentNormalIndex + 0];
			float ny = attrib.normals[3 * currentNormalIndex + 1];
			float nz = attrib.normals[3 * currentNormalIndex + 2];

			glm::vec3 normal = glm::vec3(nx, ny, nz);
			vertexData.normal = normal;

			//	Get the texture index.
			int currentTextureIndex = shapes[s].mesh.indices[i].texcoord_index;

			currentVertexArray.push_back(vertexData);
		}

		//	Add this list of indices to the list of lists of indices.
		currentIndicesArrays.push_back(currentIndicesArray);

		//	Add this list of vertices to the list of lists of vertices.
		currentVertexArrays.push_back(currentVertexArray);
	}



	if (currentIndicesArrays.size() == 1)
	{
		//	Create the geometry data of this pair of indices and vertices.
		newGeometryList.push_back(std::make_pair(baseModelName, std::make_shared<GeometryData>(GL_TRIANGLES, currentIndicesArrays[0], currentVertexArrays[0])));
	}
	else
	{
		//	Iterate over the list of lists of indices.	
		for (int i = 0; i < currentIndicesArrays.size(); i++)
		{
			//	Create the geometry data of this pair of indices and vertices.
			std::shared_ptr<GeometryData> newGeometryDataElement = std::make_shared<GeometryData>(GL_TRIANGLES, currentIndicesArrays[i], currentVertexArrays[i]);
			newGeometryList.push_back(std::make_pair(baseModelName + std::to_string(i), newGeometryDataElement));
		}
	}


	for (int i = 0; i < materials.size(); i++)
	{
		std::shared_ptr<MaterialData> newMaterialData = std::make_shared<MaterialData>();

		newMaterialData->diffuseAlbdeo.x = materials[i].diffuse[0];
		newMaterialData->diffuseAlbdeo.y = materials[i].diffuse[1];
		newMaterialData->diffuseAlbdeo.z = materials[i].diffuse[2];

		newMaterialData->specularAlbedo.x = materials[i].specular[0];
		newMaterialData->specularAlbedo.y = materials[i].specular[1];
		newMaterialData->specularAlbedo.z = materials[i].specular[2];

		newMaterialData->emissiveColor.x = materials[i].emission[0];
		newMaterialData->emissiveColor.y = materials[i].emission[1];
		newMaterialData->emissiveColor.z = materials[i].emission[2];

		newMaterialData->metallicRoughnessFresnelOpacity.x = materials[i].metallic;
		newMaterialData->metallicRoughnessFresnelOpacity.y = materials[i].roughness;
		newMaterialData->metallicRoughnessFresnelOpacity.z = materials[i].ior;
		newMaterialData->metallicRoughnessFresnelOpacity.w = 1.0;
		
		std::string newMaterialName = baseModelName + "_Material_" + std::to_string(i);
		newMaterialsList.push_back(std::make_pair(newMaterialName, newMaterialData));
	}
}
