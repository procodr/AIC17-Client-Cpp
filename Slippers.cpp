#include "Slippers.h"

Slippers::Slippers(int id, Cell pos)
    : Entity(id, pos) {this->entityType = EntityType::SLIPPERS;}