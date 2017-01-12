#pragma once

#include <random>
#include <time.h>
#include <thread>
#include <memory>
#include <chrono>
#include <mutex>

//	Thread-Safe Random Number Generators.
namespace RNGs {

	/**
	Generate a random integer between the two specified limits of the closed interval, [min, max].
	Thread-safe functions.
	Source: http://stackoverflow.com/questions/21237905/how-do-i-generate-thread-safe-uniform-random-numbers
	*/
	static int intRand(const int & min, const int & max) {

		//	Thread local random generator, randomly seeded.
		static thread_local std::mt19937 generator(std::random_device{}());

		//	Create the appropriate distribution.
		std::uniform_int_distribution<int> distribution(min, max);

		//	Return the random integer.
		return distribution(generator);
	}


	/**
	Generate a random float between the two specified limits of the half-open interval, [min, max).
	Thread-safe functions.
	Source: http://stackoverflow.com/questions/29709897/c-thread-safe-uniform-distribution-random-number-generation
	*/
	static double doubleRand(double min, double max) {

		//	Thread local random generator, randomly seeded.
		static thread_local std::mt19937 generator(std::random_device{}());

		//	Create the appropriate distribution.
		std::uniform_real_distribution<double> distribution(min, max);

		//	Return the random real number.
		return distribution(generator);
	}


}
