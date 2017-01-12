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

//	VERTEX ATTRIBUTES. POSITION, NORMAL, COLOR.
layout (location = 0) in vec4 v_vertexPosition;

//	FRAGMENT OUTPUT COLOR.
//	FRAGMENT COLOR OUT.
layout (location = 0) out vec4 o_baseOutputColor;

//	G BUFFER TEXTURES FOR SECOND PASS OF DEFERRED RENDERING.
layout (binding = 20) uniform sampler2D g_worldSpaceVertexPosition;
layout (binding = 21) uniform sampler2D g_worldSpaceVertexNormalAndDepth;
layout (binding = 22) uniform sampler2D g_diffuseAlbedoAndLitType;
layout (binding = 23) uniform sampler2D g_specularAlbedoAndLightingType;
layout (binding = 24) uniform sampler2D g_metallicnessRoughnessFresnelOpacity;
layout (binding = 25) uniform sampler2D g_emissionColorAndIntensity;


//	Post Process Textures.
layout (binding = 35) uniform sampler2D pp_inputTextureOne;
layout (binding = 36) uniform sampler2D pp_inputTextureTwo;
layout (binding = 37) uniform sampler2D pp_inputTextureThree;
layout (binding = 38) uniform sampler2D pp_inputTextureFour;

//	AMBIENT LIGHT.
uniform vec4 u_ambientLight;

//	LIGHT DESCRIPTION STRUCT.
struct Light
{
	//	Light Enabled, Locality, Light Type.
	vec4 lightEnabledShadowLightType;

	//	Vector of Options: 
	vec4 lightPosition;

	//	Vector of Options: 
	vec4 lightColorAndLightIntensity;

	//	Vector of Options: 
	vec4 lightConeDirection;

	//	Vector of Options: 
	vec4 lightAttenuationAndDistance;

	//	Vector of Options: 
	vec4 lightSpotCosCutOffAndExponent;

	//	Light Color Map.
	sampler2D mainLightColorMap;

	//	Depth Color Map.
	sampler2D mainLightDepthMap;
};


//	THE ARRAY OF LIGHTS.
uniform Light u_lights[MAX_LIGHTS];

//	Compute the Vertex - Light values from the textures. 
void getLightingProperties(in int lightIndex, out vec3 worldspace_vertexToEye, out vec3 worldspace_vertexToLightDirection, out vec3 worldspace_vertexNormal, out vec3 worldspace_reflectedLightDirection, out vec3 worldspace_halfVector, out vec3 lightColor, out float lightIntensity)
{
	//	Compute the World Space Vertex Position.
	vec3 worldspace_vertexPosition = (texture(g_worldSpaceVertexPosition, v_vertexPosition.xy).xyz);

	//	Compute the World Space Light Position.
	vec3 worldspace_lightPosition = u_lights[lightIndex].lightPosition.xyz / u_lights[lightIndex].lightPosition.w;

	//	Compute the Vertex to Eye Direction.
	worldspace_vertexToEye = normalize(u_worldCameraPosition.xyz - worldspace_vertexPosition);

	//	Compute the Vertex Normal.
	worldspace_vertexNormal = (texture(g_worldSpaceVertexNormalAndDepth, v_vertexPosition.xy).xyz);

	//	Compute the Vertex to Light Direction.
	worldspace_vertexToLightDirection = normalize(worldspace_lightPosition - worldspace_vertexPosition);

	//	Compute the Reflected Light Direction.
	worldspace_reflectedLightDirection = normalize(reflect(-worldspace_vertexToLightDirection, worldspace_vertexNormal));

	//	Compute the World Space Half Vector.
	worldspace_halfVector = (normalize(worldspace_vertexToLightDirection + worldspace_vertexToEye));

	//	Compute the Light Color.
	lightColor = u_lights[lightIndex].lightColorAndLightIntensity.xyz;

	//	Compute the Light Intensity.
	lightIntensity = u_lights[lightIndex].lightColorAndLightIntensity.w;	
}


//	Compute the Diffuse Light Color.
void computeDiffuseLightColor(in int lightIndex, in vec3 V, in vec3 L, in vec3 N, in vec3 R, in vec3 H, out vec3 diffuseColor)
{
	//	Sample the Diffuse Albedo and Lit Type.
	vec4 diffuseAlbedoAndLitType = (texture(g_diffuseAlbedoAndLitType, v_vertexPosition.xy));
	float NdotL = clamp(dot(N, L), 0.0, 1.0);


	diffuseColor = NdotL * diffuseAlbedoAndLitType.xyz;
}

//	Compute the Specular Light Color.
void computeSpecularLightColor(in int lightIndex, in vec3 V, in vec3 L, in vec3 N, in vec3 R, in vec3 H, out vec3 specularColor)
{

	//	Sample the Specular Albedo and Lighting Type.
	vec4 specularAlbedoAndLightingType = (texture(g_specularAlbedoAndLightingType, v_vertexPosition.xy));
	vec4 mrfo = (texture(g_metallicnessRoughnessFresnelOpacity, v_vertexPosition.xy));

	float NdotH = clamp(dot(N, H), 0.0, 1.0);
	float expo = pow(2.0, 1.0 / mrfo.y);
	float specIntensity = pow(NdotH, expo);
		
	specularColor = specIntensity * specularAlbedoAndLightingType.xyz;
}


//	Compute the Current Light Color.
vec3 computeCurrentLightColor(int lightIndex)
{
	//	Compute the vectors.
    vec3 V = vec3(0.0, 0.0, 0.0);
	vec3 L = vec3(0.0, 0.0, 0.0);
	vec3 N = vec3(0.0, 0.0, 0.0);
	vec3 R = vec3(0.0, 0.0, 0.0);  
    vec3 H = vec3(0.0, 0.0, 0.0);

	vec3 lightColor = vec3(0.0, 0.0, 0.0);
	float lightIntensity = 0.0;

	getLightingProperties(lightIndex, V, L, N, R, H, lightColor, lightIntensity);

	vec3 diffuseColor = vec3(0.0, 0.0, 0.0);
	computeDiffuseLightColor(lightIndex, V, L, N, R, H, diffuseColor);

	vec3 specularColor = vec3(0.0, 0.0, 0.0);
	computeSpecularLightColor(lightIndex, V, L, N, R, H, specularColor);

	return diffuseColor + specularColor;
}



//	THE FRAGMENT SHADER MAIN.
void main(void)
{

	//	Set the Final Light Color.
	vec3 totalLightColor = vec3(0.0, 0.0, 0.0);

	//	Sample the Diffuse Albedo and Lit Type.
	vec4 diffuseAlbedoAndLitType = (texture(g_diffuseAlbedoAndLitType, v_vertexPosition.xy));

	//	
	if(diffuseAlbedoAndLitType.w == 0.0)
	{
		//
		for(int i = 0; i < MAX_LIGHTS; i++)
		{
			//	
			if(u_lights[i].lightEnabledShadowLightType[0] == 1.0)
			{
				//	Set the Current Light Color.	
				vec3 currentLightColor = vec3(0.0, 0.0, 0.0);

				//	Get the Current Light Color.
				currentLightColor = computeCurrentLightColor(i);

				//	Add the Current Light Color to the Total Light Color.
				totalLightColor = totalLightColor + currentLightColor;
			}		
		}
	}


	//	Output the Color.
	o_baseOutputColor = vec4(totalLightColor, 1.0);
}