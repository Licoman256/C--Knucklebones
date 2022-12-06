#pragma once
#include <random>
namespace random {
	extern std::mt19937 rng;    // Random-number engine used (Mersenne-Twister in this case)
	extern std::uniform_int_distribution<int> randomDice;
	extern std::uniform_int_distribution<int> randomGroup; // Guaranteed unbiased
}
