#version 430 core

// CONSTANTS - PI
const float PI = 3.1415926535897932384626433832795;
const float PI_2 = 1.57079632679489661923;
const float PI_4 = 0.785398163397448309616;

//	MAX LIGHTS
#define MAX_LIGHTS 16

//	CAMERA DATA. UNIFORM CAMERA POSITION, CAMERA PERSPECTIVE MATRIX, CAMERA VIEW MATRIX.
layout (location = 10) uniform vec4 u_worldCameraPosition;
layout (location = 11) uniform mat4 u_cameraPerspectiveMatrix;
layout (location = 12) uniform mat4 u_cameraViewMatrix;
layout (location = 13) uniform mat4 u_inverseTransposeCameraViewMatrix;
layout (location = 14) uniform mat4 u_screenSpaceViewMatrix;
layout (location = 15) uniform vec4 u_cameraNearFarPlaneDistance;

//	VERTEX ATTRIBUTES - VERTEX TEXTURE COORDINATES.
layout (location = 0) in vec4 v_vertexTextureCoordinates;

//	FRAGMENT OUTPUT COLOR.
layout (location = 0) out vec4 o_baseOutputColor;

//	G BUFFER TEXTURES FOR SECOND PASS OF DEFERRED RENDERING.
layout (binding = 20) uniform sampler2D g_worldSpaceVertexPosition;
layout (binding = 21) uniform sampler2D g_worldSpaceVertexNormalAndDepth;
layout (binding = 24) uniform sampler2D g_diffuseAlbedoAndLitType;
layout (binding = 25) uniform sampler2D g_specularAlbedoAndLightingType;
layout (binding = 26) uniform sampler2D g_emissionColorAndIntensity;
layout (binding = 27) uniform sampler2D g_metallicnessRoughnessFresnelOpacity;

//	Light Color And Depth Cube Map.
layout (binding = 30) uniform samplerCube lightColorCubeMap;
layout (binding = 31) uniform samplerCube lightDepthCubeMap;

//	Vector of Options: Light Enabled, Locality, Light Type.
uniform vec4 lightEnabledShadowLightType;

//	Vector of Light Position.
uniform vec4 lightPosition;

//	Vector of Light Color and Intensity. 
uniform vec4 lightColorAndLightIntensity;

//	Vector of Light Cone Direction.
uniform vec4 lightConeDirection;

//	Vector of Light Attenuation and Distance.
uniform vec4 lightAttenuationAndDistance;

//	Vector of Light Spot Cosine Cutoff and Exponent Falloff.
uniform vec4 lightSpotCosCutOffAndExponent;


float computeShadowingFactor()
{
	//	Compute the World Space Vertex Position.
	vec3 worldspace_vertexPosition = texture(g_worldSpaceVertexPosition, v_vertexTextureCoordinates.xy).xyz;

	//	Compute the World Space Light Position.
	vec3 worldspace_lightPosition = lightPosition.xyz / lightPosition.w;

	//	Compute the Vertex Normal.	
	vec3 worldspace_vertexNormal = normalize(texture(g_worldSpaceVertexNormalAndDepth, v_vertexTextureCoordinates.xy).xyz);

	//	Compute the Vertex to Light Direction.
	vec3 worldspace_vertexToLight = worldspace_vertexPosition - worldspace_lightPosition;

	//	Find the Closest Depth of the Light.
	float closestDepth = texture(lightColorCubeMap, normalize(worldspace_vertexToLight)).x;

	//	Compute the Current Depth.
	float currentDepth = length(worldspace_vertexToLight) / u_cameraNearFarPlaneDistance[1];

	//	The Shadow Bias.
	float bias = 0.0005;  

	//	Compute the Shadowing Factor.
	float shadowingFactor = currentDepth  - bias > closestDepth ? 1.0 : 0.0;

	//	Return the Shadowing Factor.		
	return shadowingFactor;
}


//	THE FRAGMENT SHADER MAIN.
void main(void)
{
	//	Initialize the Total Light.
	vec3 totalLightResult = vec3(0.0, 0.0, 0.0);

	//	Account for the Shadowing Factor.	
	float shadowingFactor = 1.0 - computeShadowingFactor();

	//	Output the Fragment Color.
	o_baseOutputColor = vec4(shadowingFactor, shadowingFactor, shadowingFactor, 1.0);
}
