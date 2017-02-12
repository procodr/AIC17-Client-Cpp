#ifndef TRASH_H
#define TRASH_H

#include "Entity.h"

class Trash : public Entity
{
    public:
    	Trash(int id, Cell* cell);
    	static int validTime;

    	int getRemainingTurns();
};

#endif /* TRASH_H */
