#version 430 core


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

//	VERTEX ATTRIBUTES. TEXTURE COORDINATES.
layout (location = 3) in vec2 a_vertexTextureCoordinates1;
layout (location = 4) in vec2 a_vertexTextureCoordinates2;


//	VERTEX ATTRIBUTES OUT.
//	VERTEX POSITION, VERTEX NORMAL, VERTEX COLOR.
layout (location = 0) out vec4 v_vertexPosition;
layout (location = 1) out vec3 v_vertexNormal;
layout (location = 2) out vec4 v_vertexColor;

//	VERTEX ATTRIBUTES OUT. 
//	VERTEX TEXTURE COORDINATES.
layout (location = 3) out vec2 v_vertexTextureCoordinates1;
layout (location = 4) out vec2 v_vertexTextureCoordinates2;

	
//	THE VERTEX SHADER MAIN.
void main(void)
{

	//	Transfer  the Vertex Position.
	v_vertexPosition = a_vertexPosition;

	//	Transfer the Vertex Normal.
	v_vertexNormal = a_vertexNormal;

	//	Transfer the Vertex Color.
	v_vertexColor = a_vertexColor;

	//	Transfer the first set of Vertex Texture Coordinates.
	v_vertexTextureCoordinates1 = a_vertexTextureCoordinates1;

	//	Transfer the second set of Vertex Texture Coordinates.
	v_vertexTextureCoordinates2 = a_vertexTextureCoordinates2;

	//	Compute the position.
	gl_Position = u_cameraPerspectiveMatrix * u_cameraViewMatrix * u_modelMatrix * a_vertexPosition;

}