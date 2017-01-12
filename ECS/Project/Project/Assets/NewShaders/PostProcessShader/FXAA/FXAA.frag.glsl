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
	

	//	Should Convert These To Uniforms or Constants.
	float u_lumaThreshold = 0.5;
	float u_mulReduce = 1.0/ 8.0;
	float u_minReduce = 1.0/ 128.0;
	float u_maxSpan = 8.0;
	
	float screenWidth = 1280;
	float screenHeight = 720;
	
	vec2 u_texelStep = 1.0 / textureSize(pp_inputTextureOne, 0); // gets size of single texel

	vec3 rgbM = texture(pp_inputTextureOne, v_vertexTextureCoordinates.xy).rgb;

	// Possibility to toggle FXAA on and off.
	// Sampling neighbour texels. Offsets are adapted to OpenGL texture coordinates. 
	vec3 rgbNW = textureOffset(pp_inputTextureOne, v_vertexTextureCoordinates.xy, ivec2(-1, 1)).rgb;
    vec3 rgbNE = textureOffset(pp_inputTextureOne, v_vertexTextureCoordinates.xy, ivec2(1, 1)).rgb;
    vec3 rgbSW = textureOffset(pp_inputTextureOne, v_vertexTextureCoordinates.xy, ivec2(-1, -1)).rgb;
    vec3 rgbSE = textureOffset(pp_inputTextureOne, v_vertexTextureCoordinates.xy, ivec2(1, -1)).rgb;

	const vec3 toLuma = vec3(0.299, 0.587, 0.114);
	
	// Convert from RGB to luma.
	float lumaNW = dot(rgbNW, toLuma);
	float lumaNE = dot(rgbNE, toLuma);
	float lumaSW = dot(rgbSW, toLuma);
	float lumaSE = dot(rgbSE, toLuma);
	float lumaM = dot(rgbM, toLuma);

	// Gather minimum and maximum luma.
	float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
	float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));
	
	// If contrast is lower than a maximum threshold ...
	if (lumaMax - lumaMin < lumaMax * u_lumaThreshold)
	{
		// ... do no AA and return.
		o_baseOutputColor = vec4(rgbM, 1.0);
		
		return;
	}  



	// Sampling is done along the gradient.
	vec2 samplingDirection;	
	samplingDirection.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    samplingDirection.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
    
    // Sampling step distance depends on the luma: The brighter the sampled texels, the smaller the final sampling step direction.
    // This results, that brighter areas are less blurred/more sharper than dark areas.  
    float samplingDirectionReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * 0.25 * u_mulReduce, u_minReduce);

	// Factor for norming the sampling direction plus adding the brightness influence. 
	float minSamplingDirectionFactor = 1.0 / (min(abs(samplingDirection.x), abs(samplingDirection.y)) + samplingDirectionReduce);
    
    // Calculate final sampling direction vector by reducing, clamping to a range and finally adapting to the texture size. 
    samplingDirection = clamp(samplingDirection * minSamplingDirectionFactor, vec2(-u_maxSpan, -u_maxSpan), vec2(u_maxSpan, u_maxSpan)) * u_texelStep;
	
	// Inner samples on the tab.
	vec3 rgbSampleNeg = texture(pp_inputTextureOne, v_vertexTextureCoordinates.xy + samplingDirection * (1.0/3.0 - 0.5)).rgb;
	vec3 rgbSamplePos = texture(pp_inputTextureOne, v_vertexTextureCoordinates.xy + samplingDirection * (2.0/3.0 - 0.5)).rgb;

	vec3 rgbTwoTab = (rgbSamplePos + rgbSampleNeg) * 0.5;  

	// Outer samples on the tab.
	vec3 rgbSampleNegOuter = texture(pp_inputTextureOne, v_vertexTextureCoordinates.xy + samplingDirection * (0.0/3.0 - 0.5)).rgb;
	vec3 rgbSamplePosOuter = texture(pp_inputTextureOne, v_vertexTextureCoordinates.xy + samplingDirection * (3.0/3.0 - 0.5)).rgb;
	
	vec3 rgbFourTab = (rgbSamplePosOuter + rgbSampleNegOuter) * 0.25 + rgbTwoTab * 0.5;   
	
	// Calculate luma for checking against the minimum and maximum value.
	float lumaFourTab = dot(rgbFourTab, toLuma);
	
	// Are outer samples of the tab beyond the edge ... 
	if (lumaFourTab < lumaMin || lumaFourTab > lumaMax)
	{
		// ... yes, so use only two samples.
		o_baseOutputColor = vec4(rgbTwoTab, 1.0); 
	}
	else
	{
		// ... no, so use four samples. 
		o_baseOutputColor = vec4(rgbFourTab, 1.0);
	}
}
