#pragma once

//	Scene Quality.
struct SceneQuality
{
	//	Screen Width and Height.
	unsigned int screenWidth = 1920;
	unsigned int screenHeight = 1080;

	//	SSAO Effects.
	unsigned int ssaoQuality = 0;

	//	Bloom Effects.
	unsigned int bloomBlur = 0;
	unsigned int bloomThreshold = 1;

	//	Shadows.
	unsigned int shadowSize = 2048;

};