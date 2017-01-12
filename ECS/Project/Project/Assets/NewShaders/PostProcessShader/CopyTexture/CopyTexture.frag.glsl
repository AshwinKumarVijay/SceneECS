#version 430 core


//	VERTEX ATTRIBUTES - VERTEX TEXTURE COORDINATES.
layout (location = 0) in vec4 v_vertexTextureCoordinates;

//	Output the Base Color.
layout (location = 0) out vec4 o_baseOutputColor;

//	Post Process Textures.
layout (binding = 35) uniform sampler2D pp_inputTextureOne;
layout (binding = 36) uniform sampler2D pp_inputTextureTwo;
layout (binding = 37) uniform sampler2D pp_inputTextureThree;
layout (binding = 38) uniform sampler2D pp_inputTextureFour;

//	THE FRAGMENT SHADER MAIN.
void main(void)
{
	//	Output the exact same color.
	o_baseOutputColor = (texture(pp_inputTextureOne, v_vertexTextureCoordinates.xy));
}