#include "TextureGeneratorSelector.h"
#include "../Resources/ResourceData/TextureData/TextureData.h"

//	Devil Initialization Flag.
bool TextureGeneratorSelector::DevILInitializationComplete;

//	Default TextureGeneratorSelector Constructor
TextureGeneratorSelector::TextureGeneratorSelector()
{
	// If the DevIL Initialization is not yet complete.
	if (DevILInitializationComplete == false)
	{
		// Run the Initialization functions.
		ilInit();

		// Check if an error flag was raised.
		ILuint devilError;
		devilError = ilGetError();

		//	Quit if an error was raised.
		if (devilError != IL_NO_ERROR) {
			printf("Devil Error (ilInit: %ls )\n", iluErrorString(devilError));
			exit(2);
		}

		//	Set the associated renderer - we probably will not be using this.
		ilEnable(IL_FORMAT_SET);
		ilFormatFunc(IL_RGBA);

		//	Complete the Initialization of te DevIL Library, and make sure it is not called.
		DevILInitializationComplete = true;
	}

}

//	Default TextureGeneratorSelector Destructor
TextureGeneratorSelector::~TextureGeneratorSelector()
{


}

//	Generate the Texture.
std::shared_ptr<TextureBufferData> TextureGeneratorSelector::generateTexture(std::string textureGenerationType, std::string textureFileName, std::string textureParameters)
{
	//	Create the new texture data.
	std::shared_ptr<TextureBufferData> newTextureBufferData = std::make_shared<TextureBufferData>();

	//	Check if the texture should be loaded in from the file.
	if (textureGenerationType == "FILE")
	{
		//	Load the Texture from File.
		loadTextureFromFile(textureFileName, newTextureBufferData);
	}

	//	Return the new texture data.
	return newTextureBufferData;
}

//	Load the Texture from file.
void TextureGeneratorSelector::loadTextureFromFile(std::string textureFileName, std::shared_ptr<TextureBufferData> newTextureBufferData)
{
	// For the moment we will only support the loading of .png files.

	//	The DevIL ID of the Image, only a temporary. All of the Image data is written to the ImageBuffer.
	ILuint devilID;
	//	Generate the Image and get the DevIL ID.
	ilGenImages(1, &devilID);
	//	Bind the Image.
	ilBindImage(devilID);

	//	Resize the currently bound image into the appropriate size, and supply the data.
	ilEnable(IL_FILE_OVERWRITE);

	// Load  the image and check if the image was successfully loaded.
	ILboolean success;
	wchar_t * convertedFileName = StringModifiers::convertToWChar_T(textureFileName.c_str());
	success = ilLoadImage(convertedFileName);
	delete convertedFileName;

	//	Check if the image Load was successful.
	if (!success) {

		//	If the Image has not been loaded, delete the image and write the error.
		ilDeleteImages(1, &devilID);

		//	Output the Error Loading Image.
		std::cout << "Error Loading Image: " << textureFileName << std::endl;

		//	Check the error code.
		ILuint devilError;

		//	Get the error code.
		devilError = ilGetError();

		//	Check if there is an error.
		if (devilError != IL_NO_ERROR) {

			//	Print the associated error.
			printf("Devil Error (ilInit: %ls ) \n", iluErrorString(devilError));
		}

	}
	else
	{
		//	Convert the image to RGBA.
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		//	Check if this is not a success,
		if (!success)
		{
			//	Check the error code.
			ILenum error;
			error = ilGetError();

			//	Output the error conversion.
			std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;

			//	Exit.
			exit(-1);
		}

		//	 If the image Load was successful, we can load the data into the provided imageBuffer.

		//	Get the width and the height.
		int sizeX = ilGetInteger(IL_IMAGE_WIDTH);
		int sizeY = ilGetInteger(IL_IMAGE_HEIGHT);

//		std::cout << "Image width         : " << ilGetInteger(IL_IMAGE_WIDTH) << std::endl;
//		std::cout << "Image height        : " << ilGetInteger(IL_IMAGE_HEIGHT) << std::endl;
//		std::cout << "Image bits per pixel: " << ilGetInteger(IL_IMAGE_BITS_PER_PIXEL) << std::endl;
//		std::cout << "Image BPP : " << ilGetInteger(IL_IMAGE_BPP) << std::endl;


		//	Get the data of the image loaded. 
		ILubyte * bytes = ilGetData();

		//	Initialize the Buffer to the appropriate size.
		newTextureBufferData->initializeTextureBufferData(bytes, sizeX, sizeY, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_FORMAT));

		//	Delete the DevIL copy of the Image.
		ilDeleteImages(1, &devilID);
	}
}

