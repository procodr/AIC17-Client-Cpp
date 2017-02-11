#include "Trash.h"

int Trash::validTime;

Trash::Trash(int id, Cell pos)
    : Entity(id, pos, EntityType::TRASH) {
}

int Trash::getRemainingTurns() {
	return Trash::validTime - this->creationTurn;
}
