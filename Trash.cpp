#include "Trash.h"

int Trash::validTime;

Trash::Trash(int id, Cell* cell)
    : Entity(id, cell, EntityType::TRASH) {
}

int Trash::getRemainingTurns() {
	return Trash::validTime - this->creationTurn;
}
