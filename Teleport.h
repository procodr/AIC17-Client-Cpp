#ifndef TELEPORT_H
#define TELEPORT_H

#include "Entity.h"

class Teleport: public Entity {
public:
	Teleport(int id, Cell pos, int destId);

	int getDestId();

private:
	int destId;

};

#endif /* TELEPORT_H */
