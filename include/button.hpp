#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

class GameManager;

class Button : public sf::Transformable, public sf::Drawable
{
public:
	Button(GameManager* game);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleEvent(const sf::Event& event);
	void update(sf::Time dt);

private:
	GameManager* mGame;

	sf::CircleShape mCircle;
	bool isVisible;
	bool isSelected;
};

#endif