#ifndef SLIPPERS_H
#define SLIPPERS_H

#include "Entity.h"

class Slippers : public Entity
{
    public:
    	Slippers(int id, Cell* cell);
    	static int validTime;

    	int getRemainingTurns();
};

#endif /* SLIPPERS_H */
