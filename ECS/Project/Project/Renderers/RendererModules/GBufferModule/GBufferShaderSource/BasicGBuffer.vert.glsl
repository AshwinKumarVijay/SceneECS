#version 430 core

// CONSTANTS - PI
const float PI = 3.1415926535897932384626433832795;
const float PI_2 = 1.57079632679489661923;
const float PI_4 = 0.785398163397448309616;

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

//	VERTEX ATTRIBUTES. POSITION, NORMAL, COLOR.
layout (location = 0) in vec4 a_vertexPosition;
layout (location = 1) in vec3 a_vertexNormal;
layout (location = 2) in vec4 a_vertexColor;


//	VERTEX ATTRIBUTES OUT.
//	VERTEX POSITION, VERTEX NORMAL, VERTEX TANGENT, VERTEX BITANGENT.
layout (location = 0) out vec4 v_vertexPosition;
layout (location = 1) out vec3 v_vertexNormal;
layout (location = 2) out vec4 v_vertexColor;

	
//	THE VERTEX SHADER MAIN.
void main(void)
{

	//	Transfer  the Vertex Position.
	v_vertexPosition = a_vertexPosition;

	//	Transfer the Vertex Normal.
	v_vertexNormal = a_vertexNormal;

	//	Transfer the Vertex Color.
	v_vertexColor = a_vertexColor;

	//	Compute the position.
	gl_Position = u_cameraPerspectiveMatrix * u_cameraViewMatrix * u_modelMatrix * a_vertexPosition;

}