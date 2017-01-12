#include "Sampler.h"
#include "../RNGs/RNGs.h"


//	Default Sampler Constructor.
Sampler::Sampler(const int & sampleNumber)
{
	generateHemisphereKernel(sampleNumber);
}


//	Default Sampler Destructor.
Sampler::~Sampler()
{

}

//	Generate the Samples on the Hemisphere Kernel.
void Sampler::generateHemisphereKernel(const int & sampleNumber)
{
	for (int i = 0; i < sampleNumber; i++)
	{
		glm::vec3 sample((RNGs::doubleRand(0.0, 1.0) * 2.0) - 1.0, (RNGs::doubleRand(0.0, 1.0) * 2.0) - 1.0, RNGs::doubleRand(0.0, 1.0));
		sample = glm::normalize(sample);
		sample *= RNGs::doubleRand(0.0, 1.0);
		float scale = ((float)i) / ((float)sampleNumber);

		scale = glm::lerp(0.1f, 1.0f, scale * scale);
		sample *= scale;
		hemisphereKernel.push_back(glm::vec4(sample, 0.0));
	}
}

//	Return the Hemisphere Kernel.
const std::vector<glm::vec4>& Sampler::viewHemisphereKernel()
{
	return hemisphereKernel;
}

//	Return the Samples on the Unit Square.
const std::vector<glm::vec4>& Sampler::viewUnitSquareSamples()
{
	return unitSquareSamples;
}
