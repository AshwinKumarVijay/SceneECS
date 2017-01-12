#pragma once

#include <vector>

#include "glm\glm.hpp"
#include "glm\gtx\compatibility.hpp"
#include "glm\gtc\constants.hpp"


class Sampler
{
public:

	//	Default Sampler Constructor.
	Sampler(const int & sampleNumber);

	//	Default Sampler Destructor.
	virtual ~Sampler();

	//	Generate the Samples on the Hemisphere Kernel.
	virtual void generateHemisphereKernel(const int & sampleNumber);

	//	Hemisphere Kernels.
	const std::vector<glm::vec4> & viewHemisphereKernel();

	//	Unit Square Samples.
	const std::vector<glm::vec4> & viewUnitSquareSamples();

private:

	//	Hemisphere Kernel.
	std::vector<glm::vec4> hemisphereKernel;

	//	unit Square Samples.
	std::vector<glm::vec4> unitSquareSamples;
};

