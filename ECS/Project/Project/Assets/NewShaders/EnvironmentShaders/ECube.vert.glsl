#version 430 core


//	CAMERA DATA. UNIFORM CAMERA POSITION, CAMERA PERSPECTIVE MATRIX, CAMERA VIEW MATRIX.
layout (location = 10) uniform vec4 u_worldCameraPosition;
layout (location = 11) uniform mat4 u_cameraPerspectiveMatrix;
layout (location = 12) uniform mat4 u_cameraViewMatrix;
layout (location = 13) uniform mat4 u_inverseTransposeCameraViewMatrix;
layout (location = 14) uniform mat4 u_screenSpaceViewMatrix;
layout (location = 15) uniform vec4 u_cameraNearFarPlaneDistance;

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
	
	//	Pass through the Vertex Position, the Vertex Normal and the Vertex Color.
	v_vertexPosition = a_vertexPosition;
	v_vertexNormal = a_vertexNormal;
	v_vertexColor = a_vertexColor;

	//	Compute the position.
	gl_Position = u_cameraPerspectiveMatrix * u_screenSpaceViewMatrix * a_vertexPosition;
}