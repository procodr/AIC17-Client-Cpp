#include "Food.h"

int Food::validTime;

Food::Food(int id, Cell pos) :
		Entity(id, pos, EntityType::FOOD) {
}

int Food::getRemainingTurns() {
	return Food::validTime - this->creationTurn;
}
