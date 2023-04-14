#include "utils.hpp"

#include <random>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>

namespace
{
	std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = createRandomEngine();
}

int randomInt(int inclusiveMin, int inclusiveMax)
{
	std::uniform_int_distribution<> distr{ inclusiveMin, inclusiveMax };
	return distr(RandomEngine);
}

int randomInt(int inclusiveMin, int inclusiveMax, std::vector<int> omitValues)
{
	if (omitValues.empty())
		return randomInt(inclusiveMin, inclusiveMax);

	int randomValue = -1;
	do
	{
		std::uniform_int_distribution<int> distr{ inclusiveMin, inclusiveMax };
		randomValue = distr(RandomEngine);
	} while (std::find(omitValues.begin(), omitValues.end(), randomValue) != omitValues.end());

	return randomValue;
}

bool doCirclesOverlap(const sf::Vector2f& aPos, const sf::Vector2f& bPos, float maxDist)
{
	return std::fabs((aPos.x - bPos.x) * (aPos.x - bPos.x) + (aPos.y - bPos.y) * (aPos.y - bPos.y)) <= ((2 * maxDist) * (2 * maxDist));
}