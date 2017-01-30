#version 430 core

// CONSTANTS - PI
const float PI = 3.1415926535897932384626433832795;
const float PI_2 = 1.57079632679489661923;
const float PI_4 = 0.785398163397448309616;

//	MAX LIGHTS
#define MAX_LIGHTS 16
#define SAMPLES 32

//	CAMERA DATA. UNIFORM CAMERA POSITION, CAMERA PERSPECTIVE MATRIX, CAMERA VIEW MATRIX.
layout (location = 10) uniform vec4 u_worldCameraPosition;
layout (location = 11) uniform mat4 u_cameraPerspectiveMatrix;
layout (location = 12) uniform mat4 u_cameraViewMatrix;
layout (location = 13) uniform mat4 u_inverseTransposeCameraViewMatrix;
layout (location = 14) uniform mat4 u_screenSpaceViewMatrix;
layout (location = 15) uniform vec4 u_cameraNearFarPlaneDistance;

//	MODEL DATA. UNIFORM MODEL, INVERSE MODEL, NORMAL MATRIX.
layout (location = 20) uniform mat4 u_modelMatrix;
layout (location = 21) uniform mat3 u_inverseTransposeModelMatrix;
layout (location = 22) uniform mat4 u_modelViewMatrix;
layout (location = 23) uniform mat3 u_inverseTransposeModelViewMatrix;

//	MATERIAL DATA. DIFFUSE ALBEDO, METALLICNESS, ROUGHNESS, FRESNEL, OPACITY.
layout (location = 25) uniform vec4 u_diffuseAlbedoAndLitType;
layout (location = 26) uniform vec4 u_specularAlbedoAndLightingType;
layout (location = 27) uniform vec4 u_emssionColorAndIntensity;
layout (location = 28) uniform vec4 u_metallicnessRoughnessFresnelOpacity;

//	VERTEX ATTRIBUTES
//	VERTEX POSITION, VERTEX NORMAL, VERTEX COLOR.
layout (location = 0) in vec4 v_vertexPosition;
layout (location = 1) in vec3 v_vertexNormal;
layout (location = 2) in vec4 v_vertexColor;

//	VERTEX ATTRIBUTES. 
//	VERTEX TEXTURE COORDINATES.
layout (location = 3) out vec2 v_vertexTextureCoordinates1;
layout (location = 4) out vec2 v_vertexTextureCoordinates2;


//	FRAGMENT OUTPUT COLOR.
//	G BUFFER TEXTURES OUT.
layout (location = 0) out vec4 o_worldSpaceVertexPosition;
layout (location = 1) out vec4 o_worldSpaceVertexNormalAndDepth;
layout (location = 2) out vec4 o_ambientColorTexture;
layout (location = 3) out vec4 o_diffuseAlbedoAndLitType;
layout (location = 4) out vec4 o_specularAlbedoAndLightingType;
layout (location = 5) out vec4 o_metallicnessRoughnessFresnelOpacity;
layout (location = 6) out vec4 o_emissionColorAndIntensity;


//	SAMPLING TEXTURES
//	ENVIRONMENT MAP SAMPLER CUBE.
layout (binding = 0) uniform samplerCube u_backgroundEnvironmentCubeMapOne;
layout (binding = 1) uniform samplerCube u_backgroundEnvironmentCubeMapTwo;
layout (binding = 2) uniform samplerCube u_backgroundEnvironmentCubeMapThree;
layout (binding = 3) uniform samplerCube u_backgroundEnvironmentCubeMapFour;

//	Environment Map Intensities.
uniform vec4 u_environmentMapIntensities;

//	Linearize the Given Depth.
float linearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_cameraNearFarPlaneDistance.x * u_cameraNearFarPlaneDistance.y) / (u_cameraNearFarPlaneDistance.y + u_cameraNearFarPlaneDistance.x - z * (u_cameraNearFarPlaneDistance.y - u_cameraNearFarPlaneDistance.x));	
}

//	THE FRAGMENT SHADER MAIN.
void main(void)
{
	//	OUPUT WORLD SPACE VERTEX DATA.

	//	Output the World Space Vertex Positon.
	vec4 worldSpaceVertexPosition = (u_modelMatrix * v_vertexPosition);
	o_worldSpaceVertexPosition = vec4((worldSpaceVertexPosition.xyz / worldSpaceVertexPosition.w), 1.0);

	//	Output the World Space Vertex Normal And Linearized Depth.
	o_worldSpaceVertexNormalAndDepth = vec4(normalize((u_inverseTransposeModelMatrix * v_vertexNormal)), linearizeDepth(gl_FragCoord.z));

	//	OUTPUT THE MATERIAL DATA.	
	//	Output the Ambient Color.
	o_ambientColorTexture = vec4(1.0, 1.0, 1.0, 1.0);

	//	Ouput the Diffuse Albedo and Lit Type.
	o_diffuseAlbedoAndLitType = u_diffuseAlbedoAndLitType;

	//	Output the Specular Albedo and Lighting Type.
	o_specularAlbedoAndLightingType = u_specularAlbedoAndLightingType;

	//	Output the Metallicness, Roughness, Fresnel and Opacity.
	o_metallicnessRoughnessFresnelOpacity = u_metallicnessRoughnessFresnelOpacity;

	//	Output the Emission Color and Intensity.
	o_emissionColorAndIntensity = u_emssionColorAndIntensity;
}