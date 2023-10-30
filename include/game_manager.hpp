#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "state.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <stack>
#include <memory>

class GameManager
{
public:
	GameManager();

	void run();

	template <typename T>
	void pushState(GameManager* game)
	{
		mStack.push(std::make_unique<T>(game));
	}
	std::unique_ptr<State> popState();

	sf::RenderWindow mWindow;

private:
	void processInput();
	void render();

private:
	static const sf::Time sTimePerFrame;

	std::stack<std::unique_ptr<State>> mStack;
};

#endif
