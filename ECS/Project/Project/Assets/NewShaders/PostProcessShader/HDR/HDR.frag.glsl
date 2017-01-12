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

//	THE FRAGMENT SHADER MAIN.
void main(void)
{
	//	Extract the Current Value of the Texture.
	vec4 current_value = (texture(pp_inputTextureOne, v_vertexTextureCoordinates.xy));
	
	//	Extract the maximum value of the texture.
	float max_value = max(current_value.x, max(current_value.y, current_value.z));
	
	//	 Compute the new value of the texture.
	vec3 new_value = current_value.xyz;
	if(max_value > 1.0) new_value = new_value / max_value;
	
	//	Output the final color.
	o_baseOutputColor = vec4(new_value, current_value.w);
}