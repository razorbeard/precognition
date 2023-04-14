#ifndef INTRO_STATE_HPP
#define INTRO_STATE_HPP

#include "state.hpp"
#include "dialog_box.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class GameManager;

class IntroState : public State
{
public:
	IntroState(GameManager* game);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time dt) override;
	virtual void draw() override;

private:
	GameManager* mGame;
	DialogBox mDialogBox;
	Intro::ID mDialogStatus;
	sf::Font mFont;

	bool isAPVisible, isGraphVisible;
	sf::Text mActionPoints, mDay;
	sf::CircleShape mAlly, mEnemy, mUnknown;
	sf::VertexArray mLines;
};

#endif