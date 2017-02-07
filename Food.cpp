#include "Food.h"

Food::Food(int id, Cell pos)
    : Entity(id, pos) {this->entityType = EntityType::FOOD;}