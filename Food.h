#ifndef FOOD_H
#define FOOD_H

#include "Entity.h"

class Food : public Entity
{
	public:
		Food(int id, Cell pos);
		static int validTime;

		int getRemainingTurns();

};

#endif /* FOOD_H */
