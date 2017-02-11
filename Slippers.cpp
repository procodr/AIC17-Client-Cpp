#include "Slippers.h"

int Slippers::validTime;

Slippers::Slippers(int id, Cell pos)
    : Entity(id, pos, EntityType::SLIPPERS) {
}

int Slippers::getRemainingTurns() {
	return Slippers::validTime - this->creationTurn;
}
