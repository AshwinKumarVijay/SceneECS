#include "GaussianBlurModule.h"


//	Default Gaussian Blur Framebuffer ID Constructor.
GaussianBlurModule::GaussianBlurModule(std::shared_ptr<Renderer> newModuleRenderer, const unsigned int & newBlurPassCount, const unsigned int & newTextureID, const unsigned int & newTextureWidth, const unsigned int & newTextureHeight)
	:RendererModule(newModuleRenderer)
{
	//	The Input Texture ID and Output Texture ID.
	textureID = newTextureID;

	//	The Texture Width and Texture Height.
	textureWidth = newTextureWidth;
	textureHeight = newTextureHeight;

	//	The Blur Pass Count.
	blurPassCount = newBlurPassCount;

	//	Create the Gaussian Blur Textures.
	createGaussianBlurTextures();

	//	Create the Gaussian Blur Framebuffers.
	createGaussianBlurFramebuffers();
}


//	Default Gaussian Blur Framebuffer ID Destructor.
GaussianBlurModule::~GaussianBlurModule()
{

}

//	Render the Gaussian Blur.
void GaussianBlurModule::renderGaussianBlurModule()
{
	//	Activate the Copy Texture Program ID.
	glUseProgram(copyTextureProgramID);

	//	Bind the Input Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, inputFramebufferID);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	
	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	
	//	Activate the Gaussian Blur Program ID.
	glUseProgram(gaussianBlurProgramID);

	//	The Blur Pass Count.
	for (unsigned int i = 0; i < blurPassCount; i++)
	{
		//	Bind the Vertical Blur Framebuffer ID.
		glBindFramebuffer(GL_FRAMEBUFFER, vbFramebufferID);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//	Upload the Gaussian Blur Textures.
		uploadGaussianBlurTextures(colorTextureOne, depthTextureOne);

		//	Bind the Default Framebuffer.
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		//	Bind the Horizontal Framebuffer ID.
		glBindFramebuffer(GL_FRAMEBUFFER, hbFramebufferID);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//	Upload the Gaussian Blur Textures.
		uploadGaussianBlurTextures(colorTextureTwo, depthTextureTwo);

		//	Bind the Default Framebuffer.
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


	}


	//	Activate the Copy Texture Program ID.
	glUseProgram(copyTextureProgramID);

	//	Bind the Output Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, outputFramebufferID);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

//	Create the Gaussian Blur Textures.
void GaussianBlurModule::createGaussianBlurTextures()
{
	

	//	Generate and Bind the Color Texture One.
	glGenTextures(1, &colorTextureOne);
	glBindTexture(GL_TEXTURE_2D, colorTextureOne);

	//	Initialize the Color Texture.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, textureWidth, textureHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//	Unbind the Color Texture One.
	glBindTexture(GL_TEXTURE_2D, 0);

	

	//	Generate and Bind the Depth Texture One.
	glGenTextures(1, &depthTextureOne);
	glBindTexture(GL_TEXTURE_2D, depthTextureOne);

	//	Initialize the Depth Texture.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, textureWidth, textureHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//	Unbind the Depth Texture One.
	glBindTexture(GL_TEXTURE_2D, 0);




	//	Generate and Bind the Color Texture Two.
	glGenTextures(1, &colorTextureTwo);
	glBindTexture(GL_TEXTURE_2D, colorTextureTwo);

	//	Initialize the Color Texture.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, textureWidth, textureHeight, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//	Unbind the Color Texture Two.
	glBindTexture(GL_TEXTURE_2D, 0);




	//	Generate and Bind the Depth Texture One.
	glGenTextures(1, &depthTextureTwo);
	glBindTexture(GL_TEXTURE_2D, depthTextureTwo);

	//	Initialize the Depth Texture.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, textureWidth, textureHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//	Unbind the Depth Texture One.
	glBindTexture(GL_TEXTURE_2D, 0);

}

//	Create the Gaussian Blur Framebuffers.
void GaussianBlurModule::createGaussianBlurFramebuffers()
{
	//	Generate and Bind the Framebuffers.
	glGenFramebuffers(1, &inputFramebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, inputFramebufferID);


	//	Bind the Appropriate Color and Depth Textures.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureOne, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, inputDepthTexture, 0);

	//	Set the Input Draw Buffers.
	GLenum inputDrawBuffers = { GL_COLOR_ATTACHMENT0 + 0 };
	glDrawBuffers(1, &inputDrawBuffers);


	//	Bind the Framebuffers.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//	--------------------------------------------------------------------------------------------------------------	//


	//	Generate and Bind the Vertical Blur Framebuffer ID.
	glGenFramebuffers(1, &vbFramebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, vbFramebufferID);

	//	Bind the Appropriate Color and Depth Textures.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureTwo, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTextureTwo, 0);

	//	Set the Draw Buffers.
	GLenum vbDrawBuffers = { GL_COLOR_ATTACHMENT0 + 0 };
	glDrawBuffers(1, &vbDrawBuffers);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//	--------------------------------------------------------------------------------------------------------------	//

	//	Generate and Bind the Horizontal Blur Framebuffer ID.
	glGenFramebuffers(1, &hbFramebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, hbFramebufferID);

	//	Bind the Appropriate Color and Depth Textures.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureOne, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTextureOne, 0);

	//	Set the Draw Buffers.
	GLenum hbDrawBuffers = { GL_COLOR_ATTACHMENT0 + 0 };
	glDrawBuffers(1, &hbDrawBuffers);

	//	Bind the Default Framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//	--------------------------------------------------------------------------------------------------------------	//


	//	Generate and the Bind the Framebuffers.s
	glGenFramebuffers(1, &outputFramebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, outputFramebufferID);

	//	Bind the Appropriate Color and Depth Textures.
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, outputDepthTexture, 0);

	//	Set the Ouput Draw Buffers.
	GLenum outputDrawBuffers = { GL_COLOR_ATTACHMENT0 + 0 };
	glDrawBuffers(1, &outputDrawBuffers);

	//	Bind the Default Framebuffers.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


//	Upload the Gaussian Blur Textures.
void GaussianBlurModule::uploadGaussianBlurTextures(const GLuint & colorTexture, const GLuint & depthTexture)
{
	//	The Active Texture.
	glActiveTexture(GL_TEXTURE0 + 35);

	//	Bind The Texture.
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	
	//	Upload the Appropriate Texture.
	glUniform1i(gaussianBlurProgramColorTextureLocation, 35);

	//	
	glActiveTexture(GL_TEXTURE0);



	//	The Active Texture.
	glActiveTexture(GL_TEXTURE0 + 36);

	//	Bind The Texture.
	glBindTexture(GL_TEXTURE_2D, depthTexture);

	//	Upload the Appropriate Texture.
	glUniform1i(gaussianBlurProgramDepthTextureLocation, 36);

	//	
	glActiveTexture(GL_TEXTURE0);

}
