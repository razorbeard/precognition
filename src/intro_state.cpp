#include "intro_state.hpp"
#include "game_state.hpp"
#include "game_manager.hpp"
#include "data.hpp"
#include "utils.hpp"

IntroState::IntroState(GameManager* game)
	: mGame(game)
	, mDialogBox(game, Intro::colonel)
	, mDialogStatus(Intro::ID::Colonel)
	, mLines(sf::Lines)
	, isAPVisible(false)
	, isGraphVisible(false)
{
	mFont.loadFromFile("resources/fonts/PressStart2P.ttf");

	mActionPoints.setString("Action Points : 3");
	mActionPoints.setFont(mFont);
	mActionPoints.setCharacterSize(18);
	mActionPoints.setPosition(70.0f, 80.0f);

	mDay.setString("DAY 5");
	mDay.setFont(mFont);
	mDay.setCharacterSize(23);
	mDay.setPosition(625.0f, 40.0f);

	mAlly.setRadius(20.0f);
	mAlly.setFillColor(sf::Color::Green);
	mAlly.setPosition(580.0f, 200.0f);
	centerOrigin(mAlly);

	mEnemy.setRadius(20.0f);
	mEnemy.setFillColor(sf::Color::Red);
	mEnemy.setPosition(450.0f, 150.0f);
	centerOrigin(mEnemy);

	mUnknown.setRadius(20.0f);
	mUnknown.setPosition(640.0f, 400.0f);
	centerOrigin(mUnknown);

	mLines.append(mAlly.getPosition());
	mLines.append(mEnemy.getPosition());
	mLines.append(mAlly.getPosition());
	mLines.append(mUnknown.getPosition());
}

void IntroState::handleEvent(const sf::Event& event)
{
	mDialogBox.handleEvent(event);

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (mDialogBox.hasFinishedAllLines() && mDialogStatus == Intro::ID::Captain)
			{
				auto k = mGame->popState();
				mGame->pushState<GameState>(mGame);
			}
		}
	}
}

void IntroState::update(sf::Time dt)
{
	if (mDialogBox.hasFinishedAllLines() && mDialogStatus == Intro::ID::Colonel)
	{
		mDialogBox.addNewMessage(Intro::captain);
		mDialogStatus = Intro::ID::Captain;
	}

	if (mDialogStatus == Intro::ID::Captain)
	{
		if (mDialogBox.getCurrentLine() == 6)
			isGraphVisible = true;

		if (mDialogBox.getCurrentLine() == 8)
			isAPVisible = true;
	}

	mDialogBox.update(dt);
}

void IntroState::draw()
{
	sf::RenderWindow& window = mGame->mWindow;

	window.clear();
	window.draw(mDialogBox);

	if (isGraphVisible)
	{
		window.draw(mAlly);
		window.draw(mEnemy);
		window.draw(mUnknown);
		window.draw(mLines);
	}

	if (isAPVisible)
	{
		window.draw(mDay);
		window.draw(mActionPoints);
	}
}