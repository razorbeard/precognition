#include "menu_state.hpp"

#include "intro_state.hpp"
#include "game_manager.hpp"
#include "utils.hpp"

MenuState::MenuState(GameManager* game)
	: mGame(game)
{
	mFont.loadFromFile("resources/fonts/PressStart2P.ttf");

	mTitle.setFont(mFont);
	mTitle.setString("Precognition");
	mTitle.setCharacterSize(64);
	mTitle.setPosition(sf::Vector2f(mGame->mWindow.getSize() / 2u) + sf::Vector2f(0.0f, -200.0f));
	centerOrigin(mTitle);

	mStart.setFont(mFont);
	mStart.setString("Start");
	mStart.setCharacterSize(32);
	mStart.setPosition(sf::Vector2f(mGame->mWindow.getSize() / 2u) + sf::Vector2f(0.0f, 100.0f));
	centerOrigin(mStart);

	mQuit.setFont(mFont);
	mQuit.setString("Quit");
	mQuit.setCharacterSize(32);
	mQuit.setPosition(sf::Vector2f(mGame->mWindow.getSize() / 2u) + sf::Vector2f(0.0f, 200.0f));
	centerOrigin(mQuit);

	mCredits.setFont(mFont);
	mCredits.setString("By Psykopath for OLC Codejam 2021 !");
	mCredits.setCharacterSize(13);
	mCredits.setPosition(20.0f, 725.0f);
	centerOrigin(mQuit);
}

void MenuState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (mStart.getFillColor() == sf::Color::Blue)
			{
				auto k = mGame->popState();
				mGame->pushState<IntroState>(mGame);
			}
			if (mQuit.getFillColor() == sf::Color::Blue)
				mGame->popState();
		}
	}
}

void MenuState::update(sf::Time dt)
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(mGame->mWindow));

	if (mStart.getGlobalBounds().contains(mousePosition))
  {
		mStart.setFillColor(sf::Color::Blue);
  }
	else
  {
		mStart.setFillColor(sf::Color::White);
  }

	if (mQuit.getGlobalBounds().contains(mousePosition))
  {
    mQuit.setFillColor(sf::Color::Blue);
  }
  else
  {
		mQuit.setFillColor(sf::Color::White);
  }
}

void MenuState::draw()
{
	sf::RenderWindow& window = mGame->mWindow;

	window.clear();
	window.draw(mTitle);
	window.draw(mStart);
	window.draw(mQuit);
	window.draw(mCredits);
}
