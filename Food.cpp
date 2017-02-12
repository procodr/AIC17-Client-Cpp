#include "Food.h"

int Food::validTime;

Food::Food(int id, Cell* cell) :
		Entity(id, cell, EntityType::FOOD) {
}

int Food::getRemainingTurns() {
	return Food::validTime - this->creationTurn;
}
