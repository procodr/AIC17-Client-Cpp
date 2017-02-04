#include "AI.h"

#include <vector>
#include <cstdlib>
#include <iostream>

void AI::doTurn(World *world)
{
	/** Fill this method. We've presented a stupid AI as an example! **/
	srand(time(NULL));
	std::vector<Node*>& myNodes = world->getMyNodes();
	for(auto& source : myNodes)
	{
		/** Get neighbours **/
		const std::vector<Node*>& neighbours = source->getNeighbours();
		if (neighbours.size() > 0)
		{
			/** Select a random neighbour **/
			Node *destination = neighbours[(int)(rand() % neighbours.size())];
			/** Move half of the nodes army to the neighbour node **/
			world->moveArmy(source, destination, source->getArmyCount() / 2);
		}
	}
}
