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

//	MATERIAL DATA. DIFFUSE ALBEDO, METALLICNESS, ROUGHNESS, FRESNEL, OPACITY.
layout (location = 25) uniform vec4 u_diffuseAlbedoAndLitType;
layout (location = 26) uniform vec4 u_specularAlbedoAndLightingType;
layout (location = 27) uniform vec4 u_emssionColorAndIntensity;
layout (location = 28) uniform vec4 u_metallicnessRoughnessFresnelOpacity;

//	VERTEX ATTRIBUTES
//	VERTEX POSITION, VERTEX NORMAL, VERTEX TANGENT, VERTEX BITANGENT.
layout (location = 0) in vec4 v_vertexPosition;
layout (location = 1) in vec3 v_vertexNormal;
layout (location = 2) in vec4 v_vertexColor;

//	MODEL DATA. UNIFORM MODEL, INVERSE MODEL, NORMAL MATRIX.
layout(location = 7) in mat4 u_modelMatrix;
layout(location = 11) in mat4 u_modelViewMatrix;
layout(location = 15) in mat3 u_inverseTransposeModelMatrix;
layout(location = 18) in mat3 u_inverseTransposeModelViewMatrix;


//	FRAGMENT OUTPUT COLOR.
//	G BUFFER TEXTURES OUT.
layout (location = 0) out vec4 o_worldSpaceVertexPosition;
layout (location = 1) out vec4 o_worldSpaceVertexNormalAndDepth;
layout (location = 2) out vec4 o_diffuseAlbedoAndLitType;
layout (location = 3) out vec4 o_specularAlbedoAndLightingType;
layout (location = 4) out vec4 o_emissionColorAndIntensity;
layout (location = 5) out vec4 o_metallicnessRoughnessFresnelOpacity;

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
	o_worldSpaceVertexPosition = (u_modelMatrix * v_vertexPosition);
	o_worldSpaceVertexPosition = vec4((o_worldSpaceVertexPosition.xyz / o_worldSpaceVertexPosition.w), 1.0);
	o_worldSpaceVertexNormalAndDepth = vec4(normalize((u_inverseTransposeModelMatrix * v_vertexNormal)), linearizeDepth(gl_FragCoord.z));
	
	//	OUTPUT MATERIAL DATA.
	o_diffuseAlbedoAndLitType = u_diffuseAlbedoAndLitType;
	o_specularAlbedoAndLightingType = u_specularAlbedoAndLightingType;
	o_emissionColorAndIntensity = u_emssionColorAndIntensity;
	o_metallicnessRoughnessFresnelOpacity = u_metallicnessRoughnessFresnelOpacity;
}