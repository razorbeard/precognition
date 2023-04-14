#include "node.hpp"
#include "utils.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

int Node::idGenerator = 0;

Node::Node()
	: mID(idGenerator++)
	, mType(Type::Unknown)
	, mFactoryLevel(0)
	, mDefenseLevel(0)
	, mTroupStrength(0)
{
	mShape.setRadius(20.0f);
	centerOrigin(mShape);
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(mShape, states);
}

void Node::setType(Node::Type type)
{
	mType = type;
	if (mType == Node::Type::Ally)
		mShape.setFillColor(sf::Color::Green);
	else if (mType == Node::Type::Enemy)
		mShape.setFillColor(sf::Color::Red);
	else if (mType == Node::Type::Unknown)
		mShape.setFillColor(sf::Color::White);
}

int Node::getID() const
{
	return mID;
}