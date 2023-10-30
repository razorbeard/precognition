#ifndef DIALOG_BOX_HPP
#define DIALOG_BOX_HPP

#include "data.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

class GameManager;

class DialogBox : public sf::Transformable, public sf::Drawable
{
public:
	DialogBox(GameManager* game, const Dialog& message);

	bool hasFinishedAllLines();
	void addNewMessage(const Dialog& message);
	int getCurrentLine() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleEvent(const sf::Event& event);
	void update(sf::Time dt);

private:
	void postTreatment(Dialog& message);
	bool hasFinishedCurrentLine();

private:
	sf::RectangleShape mBox;
	sf::CircleShape mArrow;
	sf::Text mDialog;
	sf::Font mFont;
	Dialog mMessage;
	Dialog mNextMessage;

	std::size_t mSubstrIdx;
	std::size_t mCurrentLine;
	sf::Time mElapsedTime;
	bool mShowArrow;
};

#endif
