#include "button.hpp"

#include <SFML/Window/Event.hpp>

#include "game_manager.hpp"
#include "utils.hpp"

Button::Button(GameManager* game)
	: mGame(game)
	, mIsVisible(true)
	, mIsSelected(false)
{
	mCircle.setRadius(8);
	centerOrigin(mCircle);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (mIsVisible)
  {
    target.draw(mCircle, states);
  }
}

void Button::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			mIsSelected = true;
		}
	}
}

void Button::update(sf::Time dt)
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(mGame->mWindow));

	if (mCircle.getGlobalBounds().contains(mousePosition))
  {
    mCircle.setFillColor(sf::Color::Yellow);
  }
  else
  {
		mCircle.setFillColor(sf::Color::White);
  }
}
