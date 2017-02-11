#include "AI.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Types.h"

void AI::doTurn(World *world)
{
    /** Fill this method. We've presented a stupid AI as an example! **/
    if (world->getCurrentTurn() == 0)
    {
		srand(time(NULL));
		for (int i = 0; i < 2; i += 1)
			for (int j = 0; j < 3; j += 1)
	    		for (int k = 0; k < 3; k += 1)
				{
					world->changeStrategy(false, static_cast<CellState>(i), static_cast<CellState>(j), static_cast<CellState>(k), static_cast<Move> (1));
					world->changeStrategy(true, static_cast<CellState>(i), static_cast<CellState>(j), static_cast<CellState>(k), static_cast<Move> (1));
				}
    }
    else
    {
		/* never change strategy :p */
    }
}
