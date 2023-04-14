#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "state.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class GameManager;

class MenuState : public State
{
public:
	MenuState(GameManager* game);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time dt) override;
	virtual void draw() override;

private:
	GameManager* mGame;

	sf::Font mFont;

	sf::Text mCredits;
	sf::Text mTitle;
	sf::Text mStart;
	sf::Text mQuit;
};

#endif