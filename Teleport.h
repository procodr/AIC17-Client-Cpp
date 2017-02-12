#ifndef TELEPORT_H
#define TELEPORT_H

#include "Entity.h"

class Teleport: public Entity {
public:
	Teleport(int id, Cell* cell, int pairId);

	Teleport* getPair();
	int getPairId();
	void setPair(Teleport* pair);

private:
	int pairId;
	Teleport* pair;
};

#endif /* TELEPORT_H */
