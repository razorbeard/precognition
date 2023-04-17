#include "graph.hpp"
#include "game_manager.hpp"
#include "utils.hpp"

Graph::Graph(GameManager* game, int size)
	: mGame(game)
	, mSize(size)
	, mNumberOfEdges(randomInt(size, size* (size - 1) / 2))
	, mEdges(sf::Lines)
	, mAdj(size)
	, mNodes(size)
{
	// Start by setting an ally and enemy base
	int allyID = randomInt(0, size - 1);
	int enemyID = randomInt(0, size - 1, { allyID });
	mNodes[allyID].setType(Node::Type::Ally);
	mNodes[enemyID].setType(Node::Type::Enemy);

	setNodesPosition();

	// Register random distance for each node: we assume our graph is connected
	// So we make sure that at least one node get linked to another one
	for (int i = 0; i < size; ++i)
	{
		std::vector<int> omitVal = getNeighbours(i);
		omitVal.push_back(i);

		// Exclude case where a node is connected to all the others
		if (omitVal.size() != size)
		{
			int secondID = randomInt(0, size - 1, omitVal);
			registerDistance(i, secondID, 10 * randomInt(13, 40)); // Distance interval = [130; 400] pixels
			mEdges.append(mNodes[i].getPosition());
			mEdges.append(mNodes[secondID].getPosition());
		}
	}

	// Finish giving edges for random nodes
	int counter = 0;
	while (counter < mNumberOfEdges - size)
	{
		int firstID = randomInt(0, size - 1);
		std::vector<int> omitVal = getNeighbours(firstID);
		omitVal.push_back(firstID);

		if (omitVal.size() != size)
		{
			int secondID = randomInt(0, size - 1, omitVal);
			registerDistance(firstID, secondID, 10 * randomInt(13, 40));
			mEdges.append(mNodes[firstID].getPosition());
			mEdges.append(mNodes[secondID].getPosition());
			counter++;
		}
	}
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw the edges
	target.draw(mEdges);
	
    // Draw the nodes
	for (auto& node : mNodes)
		node.draw(target, states);
}

void Graph::registerDistance(int id1, int id2, int distance)
{
	// Distance is expressed in pixels
	mAdj[id1].push_back(std::make_pair(id2, distance));
	mAdj[id2].push_back(std::make_pair(id1, distance));
}

std::vector<int> Graph::getNeighbours(int id) const
{
	std::vector<int> neighbours;
	for (auto& list : mAdj[id])
		neighbours.push_back(list.first);

	return neighbours;
}

int Graph::getSize() const
{
	return mSize;
}

void Graph::setNodesPosition()
{
	// Arbitrary values
	int xmin = 450, xmax = 950;
	int ymin = 150, ymax = 470;

	// Adjust to get more distance between each node
	// Be careful, if there's too much nodes => infinite loop below
	float maxRadius = 40.0f - mSize;

	// Set two random nodes to see the limits
	std::vector<int> visited;
	int randNodeLeft = randomInt(0, mSize - 1);
	mNodes[randNodeLeft].setPosition(xmin, randomInt(ymin, ymax));
	visited.push_back(randNodeLeft);

	int randNodeRight = randomInt(0, mSize - 1, visited);
	mNodes[randNodeRight].setPosition(xmax, randomInt(ymin, ymax));
	visited.push_back(randNodeRight);

	// Then finish with other nodes
	for (int i = 0; i < mSize - 2; ++i)
	{
		int idx = randomInt(0, mSize - 1, visited);
		sf::Vector2f pos;

		// Perform a pseudo-collision check between each node to get better representation
		std::vector<bool> collisionFound;
		do
		{
			collisionFound.clear();
			pos = sf::Vector2f(randomInt(xmin, xmax), randomInt(ymin, ymax));

			for (int k = 0; k < mSize; ++k)
			{
				if (k != idx && doCirclesOverlap(pos, mNodes[k].getPosition(), maxRadius))
					collisionFound.push_back(true);
			}
		} while (!collisionFound.empty());

		mNodes[idx].setPosition(pos);
		visited.push_back(idx);
	}
}
