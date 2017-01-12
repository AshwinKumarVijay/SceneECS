#version 430 core

//	MAX LIGHTS
#define MAX_LIGHTS 16
#define SAMPLES 256

//	VERTEX ATTRIBUTES. POSITION, NORMAL, COLOR.
layout (location = 0) in vec4 v_vertexPosition;

//	FRAGMENT OUTPUT COLOR.
//	FRAGMENT COLOR OUT.
layout (location = 0) out vec4 o_baseOutputColor;

//	Input the Post Process Texture.
layout (binding = 35) uniform sampler2D pp_inputTextureOne;			
layout (binding = 36) uniform sampler2D pp_inputTextureTwo;			
layout (binding = 37) uniform sampler2D pp_inputTextureThree;		
layout (binding = 38) uniform sampler2D pp_inputTextureFour;		

//	Blur Direction.
uniform bool isBlurHorizontal;

//		
uniform float weights[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

//	THE VERTEX SHADER MAIN.
void main(void)
{
	
	vec2 tex_offset = 1.0 / textureSize(pp_inputTextureOne, 0); // gets size of single texel
    vec3 result = texture(pp_inputTextureOne, v_vertexPosition.xy).rgb * weights[0]; // current fragment's contribution

    if(isBlurHorizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(pp_inputTextureOne, v_vertexPosition.xy + vec2(tex_offset.x * i, 0.0)).rgb * weights[i];
            result += texture(pp_inputTextureOne, v_vertexPosition.xy - vec2(tex_offset.x * i, 0.0)).rgb * weights[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(pp_inputTextureOne, v_vertexPosition.xy + vec2(0.0, tex_offset.y * i)).rgb * weights[i];
            result += texture(pp_inputTextureOne, v_vertexPosition.xy - vec2(0.0, tex_offset.y * i)).rgb * weights[i];
        }
    }


    o_baseOutputColor = vec4(result, 1.0);
	
}