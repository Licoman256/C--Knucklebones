#include "random.h"
#include "field.h"
namespace random {
	std::random_device rd;         // Only used once to initialise (seed) engine
	extern std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
	extern std::uniform_int_distribution<int> randomDice(1, 6);
	extern std::uniform_int_distribution<int> randomGroup(0, countGroupsPerPlayer);// Guaranteed unbiased
}