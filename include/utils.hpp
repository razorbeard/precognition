#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>

#include <random>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>

int randomInt(int inclusiveMin, int inclusiveMax);
int randomInt(int inclusiveMin, int inclusiveMax, std::vector<int> omitValues);

// This function is only used for visual representation of the graph
bool doCirclesOverlap(const sf::Vector2f& aPos, const sf::Vector2f& bPos, float maxDist);

template <typename T>
void centerOrigin(T& obj)
{
	sf::FloatRect bounds{ obj.getLocalBounds() };
	obj.setOrigin(std::floor(bounds.left + bounds.width / 2.0f),
				  std::floor(bounds.top + bounds.height / 2.0f));
}

#endif