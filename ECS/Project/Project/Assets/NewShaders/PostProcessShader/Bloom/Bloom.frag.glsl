#version 430 core


//	VERTEX ATTRIBUTES - VERTEX TEXTURE COORDINATES.
layout (location = 0) in vec4 v_vertexTextureCoordinates;

//	Output the Base Color.
layout (location = 0) out vec4 o_baseOutputColor;

//	Input the Texture.
layout (binding = 35) uniform sampler2D pp_inputTextureOne;
layout (binding = 36) uniform sampler2D pp_inputTextureTwo;
layout (binding = 37) uniform sampler2D pp_inputTextureThree;
layout (binding = 38) uniform sampler2D pp_inputTextureFour;

//	The Threshold Value.
uniform float u_extractionValue;

//	THE FRAGMENT SHADER MAIN.
void main(void)
{
	//	Check the Current Value and Extract it if it is above the threshold.
	vec4 current_value = (texture(pp_inputTextureOne, v_vertexTextureCoordinates.xy));

	float max_value = max(current_value.x, max(current_value.y, current_value.z));

	if(max_value > u_extractionValue)
	{
		o_baseOutputColor = vec4(current_value.xyz, current_value.w);
	}
	else
	{
		o_baseOutputColor = vec4(0.0, 0.0, 0.0, current_value.w);
	}
}
