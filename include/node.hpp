#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Node : public sf::Transformable, public sf::Drawable
{
public:
	enum class Type
	{
		Ally,
		Enemy,
		Unknown
	};

public:
	Node();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setType(Node::Type type);
	int getID() const;

private:
	static int idGenerator;
	sf::CircleShape mShape;

	int mID;
	Node::Type mType;

	int mFactoryLevel;
	int mDefenseLevel;
	int mTroupStrength;
};

#endif