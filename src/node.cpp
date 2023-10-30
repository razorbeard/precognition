#include "node.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "utils.hpp"

int Node::sIdGenerator = 0;

Node::Node()
	: mID(sIdGenerator++)
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

  switch (mType)
  {
  case (Node::Type::Ally):
		mShape.setFillColor(sf::Color::Green);
    break;
  case (Node::Type::Enemy):
		mShape.setFillColor(sf::Color::Red);
    break;
  case (Node::Type::Unknown):
		mShape.setFillColor(sf::Color::White);
    break;
  default:  
    break;
  }
}

int Node::getID() const
{
	return mID;
}
