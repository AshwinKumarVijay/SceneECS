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

//	MODEL DATA. UNIFORM MODEL, INVERSE MODEL, NORMAL MATRIX.
layout (location = 20) uniform mat4 u_modelMatrix;
layout (location = 21) uniform mat3 u_inverseTransposeModelMatrix;
layout (location = 22) uniform mat4 u_modelViewMatrix;
layout (location = 23) uniform mat3 u_inverseTransposeModelViewMatrix;

//	VERTEX ATTRIBUTES
//	VERTEX POSITION, VERTEX NORMAL, VERTEX TANGENT, VERTEX BITANGENT.
layout (location = 0) in vec4 v_vertexPosition;
layout (location = 1) in vec3 v_vertexNormal;
layout (location = 2) in vec4 v_vertexColor;

//	FRAGMENT OUTPUT COLOR.
layout (location = 0) out vec4 o_baseOutputColor;


//	THE FRAGMENT SHADER MAIN.
void main(void)
{
	//	Get the Vertex Position in World Space.
	vec4 worldspace_vertexposition =  (u_modelMatrix * v_vertexPosition);
	
	//	Get the Compute the Light Distance.
	float lightDistance = length(worldspace_vertexposition.xyz - u_worldCameraPosition.xyz);

	//	Map this into the range of 0 to 1.
	lightDistance = lightDistance / u_cameraNearFarPlaneDistance[1];

	//	Output the Light Distance.	
	o_baseOutputColor = vec4(lightDistance, lightDistance, lightDistance, 1.0);
}

