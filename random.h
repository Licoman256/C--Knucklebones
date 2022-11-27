#pragma once
#include <random>
namespace random {
	std::random_device rd;     // Only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 6); // Guaranteed unbiased
}
