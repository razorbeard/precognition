#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "node.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <list>
#include <utility>
#include <vector>

class GameManager;

class Graph : public sf::Transformable, public sf::Drawable
{
public:
	Graph(GameManager* game, int size);

	std::vector<int> getNeighbours(int id) const;
	void registerDistance(int id1, int id2, int distance);
	int getSize() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void handleEvent(const sf::Event& event);
	void update(sf::Time dt);

private:
	void setNodesPosition();

private:
	GameManager* mGame;

	int mSize;
	int mNumberOfEdges;

	sf::VertexArray mEdges;

	std::vector<std::list<std::pair<int, int>>> mAdj;
	std::vector<Node> mNodes;
};

#endif