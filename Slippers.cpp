#include "Slippers.h"

int Slippers::validTime;

Slippers::Slippers(int id, Cell* cell)
    : Entity(id, cell, EntityType::SLIPPERS) {
}

int Slippers::getRemainingTurns() {
	return Slippers::validTime - this->creationTurn;
}
