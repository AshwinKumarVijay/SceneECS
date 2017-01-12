#pragma once

#include <vector>
#include <sstream>
#include <iostream>
#include <memory>
#include <map>
#include <algorithm>

#include "GL\glew.h"

#include "../Vertex/Vertex.h"

//	The struct for one drawing command - Instanced. Not used yet.
struct DrawArraysIndirectCommand
{
	unsigned int  count;
	unsigned int  primCount;
	unsigned int  first;
	unsigned int  baseInstance;
};

//	The struct for one drawing command - Elements, Instanced. Not used yet.
struct DrawElementsIndirectCommand {

	unsigned int  vertexCount;
	unsigned int  instanceCount;
	unsigned int  firstIndex;
	unsigned int  baseVertex;
	unsigned int  baseInstance;

};

//	The Struct for the Environment CubeMap Data.
struct BackgroundEnvironmentData
{
	//
	glm::vec4 backgroundEnvironmentCubeMapsIntensities = glm::vec4(1.0, 1.0, 1.0, 1.0);

	//	The Environment Cube Maps, by name.
	std::string backgroundEnvironmentCubeMaps[4];

	//	Environment Maps VAO
	GLuint backgroundEnvironmentVAO;

	//	Environment Maps VBO
	GLuint backgroundEnvironmentCubeMapVBO;

	//	Skybox Data
	std::vector<Vertex> skyboxVertices;
};


//	The Struct for the Light Data
struct RendererLightBufferObject
{
	//	Maximum Number of Lights.
	int maximumNumberOfLights;

	//	Light Binding Index.
	GLuint lightBindingIndex;

	//	The Uniform Buffer Object for Lights.
	GLuint lightBufferObject;
};


//	Renderer Pipeline Framebuffer.
struct RendererPipelineFramebuffer
{
	GLuint framebufferID = 0;
};

//	Renderer Pipeline Texture.
struct RendererPipelineTexture
{
	GLuint textureID = 0;
};

//	The Noise Textures.
struct RendererNoiseTextures
{
	GLuint noiseTextureOneID = 0;
	GLuint noiseTextureTwoID = 0;
	GLuint noiseTextureThreeID = 0;
	GLuint noiseTextureFourID = 0;
};


