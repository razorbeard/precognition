#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "state.hpp"
#include "dialog_box.hpp"
#include "graph.hpp"
#include "button.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <utility>

class GameManager;

class GameState : public State
{
public:
	GameState(GameManager* game);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time dt) override;
	virtual void draw() override;

private:
	GameManager* mGame;
	sf::Font mFont;
	sf::Text mAPText;
	sf::Text mDayText;
	sf::Text mBaseID;
	sf::Text mLevels;
	std::vector<std::vector<Button>> mButtons; // 4 buttons for each node

	sf::Sprite mIcons;
	sf::Texture mTexture;

	DialogBox mDialogBox;
	Graph mGraph;

	int mDay;
	int mActionPoints;
};

#endif