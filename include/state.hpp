#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Window/Event.hpp>

class GameManager;

class State
{
public:
	virtual void handleEvent(const sf::Event& event) = 0;
	virtual void update(sf::Time dt) = 0;
	virtual void draw() = 0;
};

#endif