#include "game_state.hpp"
#include "game_manager.hpp"
#include "utils.hpp"
#include "data.hpp"

GameState::GameState(GameManager* game)
	: mGame(game)
	, mGraph(game, randomInt(7, 8))
	, mDialogBox(game, Game::playerTurn)
	, mDay(1)
	, mActionPoints(3)
{
	mTexture.loadFromFile("resources/textures/icons.png");
	mIcons.setTexture(mTexture);
	mIcons.setPosition(120.0f, 125.0f);

	mFont.loadFromFile("resources/fonts/PressStart2P.ttf");

	mAPText.setString("Action Points : " + std::to_string(mActionPoints));
	mAPText.setFont(mFont);
	mAPText.setCharacterSize(18);
	mAPText.setPosition(70.0f, 80.0f);

	mDayText.setString("DAY " + std::to_string(mDay));
	mDayText.setFont(mFont);
	mDayText.setCharacterSize(23);
	mDayText.setPosition(625.0f, 40.0f);

	std::string basesID;
	for (int i = 0; i < mGraph.getSize(); ++i)
		basesID.append("Base " + std::to_string(i) + "\n\n\n");

	mBaseID.setString(basesID);
	mBaseID.setFont(mFont);
	mBaseID.setCharacterSize(13);
	mBaseID.setPosition(24.0f, 192.0f);

	std::string levels;
	for (int i = 0; i < mGraph.getSize(); ++i)
		levels.append("0/20\n\n\n");

	mLevels.setString(levels);
	mLevels.setFont(mFont);
	mLevels.setCharacterSize(13);
	mLevels.setPosition(335.0f, 192.0f);

	mButtons = std::vector<std::vector<Button>>(mGraph.getSize(), std::vector<Button>(4, game));
	sf::Vector2f pos = { 135.0f, 192.0f };
	for (int i = 0; i < mGraph.getSize(); ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mButtons[i][j].setPosition(pos);
			pos.x += 50.0f;
		}
		pos.x = 135.0f;
		pos.y += 40.0f;
	}
}

void GameState::handleEvent(const sf::Event& event)
{
	mDialogBox.handleEvent(event);

	for (auto& row : mButtons)
	{
		for (auto& col : row)
		{
			col.handleEvent(event);
		}
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
		}
	}
}

void GameState::update(sf::Time dt)
{
	mDialogBox.update(dt);

	for (auto& row : mButtons)
	{
		for (auto& col : row)
		{
			col.update(dt);
		}
	}

	// ?
	mAPText.setString("Action Points : " + std::to_string(mActionPoints));
	mDayText.setString("DAY " + std::to_string(mDay));
}

void GameState::draw()
{
	sf::RenderWindow& window = mGame->mWindow;

	window.clear();
	window.draw(mDialogBox);
	window.draw(mGraph);
	window.draw(mAPText);
	window.draw(mDayText);
	window.draw(mBaseID);
	window.draw(mIcons);
	window.draw(mLevels);

	for (auto& row : mButtons)
	{
		for (auto& col : row)
		{
			window.draw(col);
		}
	}
}