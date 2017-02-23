#version 430 core

//	MAX LIGHTS
#define MAX_LIGHTS 16
#define SAMPLES 16

//	CAMERA DATA. UNIFORM CAMERA POSITION, CAMERA PERSPECTIVE MATRIX, CAMERA VIEW MATRIX.
layout (location = 10) uniform vec4 u_worldCameraPosition;
layout (location = 11) uniform mat4 u_cameraPerspectiveMatrix;
layout (location = 12) uniform mat4 u_cameraViewMatrix;
layout (location = 13) uniform mat3 u_inverseTransposeCameraViewMatrix;
layout (location = 14) uniform mat4 u_screenSpaceViewMatrix;
layout (location = 15) uniform vec4 u_cameraNearFarPlaneDistance;

//	VERTEX ATTRIBUTES. POSITION, NORMAL, COLOR.
layout (location = 0) in vec4 v_vertexPosition;

//	FRAGMENT OUTPUT COLOR.
//	FRAGMENT COLOR OUT.
layout (location = 0) out vec4 o_baseOutputColor;

//	Input the Post Process Texture.
layout (binding = 35) uniform sampler2D pp_inputTextureOne;			//	World Vertex Position.
layout (binding = 36) uniform sampler2D pp_inputTextureTwo;			//	World Space Vertex Normal And Depth.
layout (binding = 39) uniform sampler2D pp_inputTextureThree;		//	Ambient Color Pass Texture.
layout (binding = 40) uniform sampler2D pp_inputTextureFour;		//	Ambient Depth Pass Texture.


//	Input the Noise Textures.
layout (binding = 45) uniform sampler2D t_noiseTextureOne;			//	Noise Texture One.
layout (binding = 46) uniform sampler2D t_noiseTextureTwo;			//	Noise Texture Two.
layout (binding = 47) uniform sampler2D t_noiseTextureThree;		//	Noise Texture Three.
layout (binding = 48) uniform sampler2D t_noiseTextureFour;			//	Noise Texture Four.

//	SAMPLING.

//	Radius.
uniform float u_hemisphereRadius;

//	Hemisphere Samples.
uniform vec4 u_hemisphereSamples[SAMPLES];


//	THE VERTEX SHADER MAIN.
void main(void)
{
	//	The Noise Scale.
	vec2 noiseScale = textureSize(pp_inputTextureOne, 0) / 4.0f;

	//	Extract World Space Vertex Position and Normal.
	vec4 worldSpaceVertexPosition = vec4(texture(pp_inputTextureOne, v_vertexPosition.xy).xyz, 1.0);
	vec3 worldSpaceVertexNormal = normalize(texture(pp_inputTextureTwo, v_vertexPosition.xy).xyz);

	//	Compute the View Space Vetex Position and Normal.
	vec4 viewSpaceVertexPosition = u_cameraViewMatrix * worldSpaceVertexPosition;
	viewSpaceVertexPosition = vec4(viewSpaceVertexPosition.xyz / viewSpaceVertexPosition.w , 1.0);
	vec3 viewSpaceVertexNormal = normalize(u_inverseTransposeCameraViewMatrix * worldSpaceVertexNormal.xyz);

	//	Compute the Random Vector.
	vec3 randomVector = normalize(((texture(t_noiseTextureOne, v_vertexPosition.xy * noiseScale).xyz)));

	//	Compute the Tangent and the Bitangent and the TBN.
	vec3 tangent = normalize(randomVector - (viewSpaceVertexNormal * dot(randomVector, viewSpaceVertexNormal)));
	vec3 bitangent = cross(viewSpaceVertexNormal, tangent);
	mat3 TBN = mat3(tangent, bitangent, viewSpaceVertexNormal);

	//	Set the occlusion factor to be zero.
	float occlusion = 0.0;

	//	The Samples Count.
	for(int i = 0; i < SAMPLES; i++)
	{
		//	Create the Sample Point Offset.
		vec3 samplePoint = (TBN * (u_hemisphereSamples[i].xyz));
		
		//	Create the Sample Point in View Space.
		samplePoint = (samplePoint * u_hemisphereRadius) + viewSpaceVertexPosition.xyz;
		
		vec4 offset = vec4(samplePoint, 1.0);
		offset = u_cameraPerspectiveMatrix * offset;
		offset.xyz  = offset.xyz / offset.w;
		offset.xyz = (offset.xyz * 0.5) + 0.5;	

		float sampleDepth = -texture(pp_inputTextureTwo, offset.xy).w;

		float rangeCheck = smoothstep(0.0, 1.0, u_hemisphereRadius / abs(samplePoint.z - sampleDepth));
		occlusion += (sampleDepth  >= samplePoint.z + 0.5 ? 1.0 : 0.0) * rangeCheck;

	}

	//	Compute the Occlusion Factor. 
	occlusion =	1.0 - (occlusion / (float(SAMPLES)));
	
	//	OUTPUT COLOR 
	o_baseOutputColor = vec4(occlusion * texture(pp_inputTextureThree, v_vertexPosition.xy).xyz, 1.0);
}