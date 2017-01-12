#version 430 core

//	VERTEX ATTRIBUTES - VERTEX TEXTURE COORDINATES.
layout (location = 0) out vec4 v_vertexTextureCoordinates;

void main(void)
{
	//	Array of the Vertex Coordinates.
	vec4 vertexPosition[4] = vec4[4](vec4(-1.0, -1.0, 0.0, 1.0), vec4(1.0, -1.0, 0.0, 1.0), vec4(-1.0, 1.0, 0.0, 1.0), vec4(1.0, 1.0, 0.0, 1.0));

	//	Array of the Texture Coordinates.
	vec2 textureCoordinates[4] = vec2[4](vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 1.0));

	//	Set the Texture Coordinates to be passed into the Fragment Shader.
	v_vertexTextureCoordinates = vec4(textureCoordinates[gl_VertexID], 0.0, 1.0);

	//	Output the position of the Vertex.
	gl_Position = vertexPosition[gl_VertexID];
}