#include "AI.h"

#include <ctime>
#include <cstdlib>
#include <iostream>

void AI::doTurn(World *world)
{
    /** Fill this method. We've presented a stupid AI as an example! **/
    if (world->getTurnNumber() == 0)
    {
		srand(time(NULL));
		for (int i = 0; i < 2; i += 1)
			for (int j = 0; j < 3; j += 1)
	    		for (int k = 0; k < 3; k += 1)
				{
					world->changeStrategy(Antenna::SINGLE, i, j, k, static_cast<Move> (1));
					world->changeStrategy(Antenna::DOUBLE, i, j, k, static_cast<Move> (1));
				}
    }
    else
    {
		/* never change strategy :p */
    }
}
