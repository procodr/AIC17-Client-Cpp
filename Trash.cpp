#include "Trash.h"

Trash::Trash(int id, Cell pos)
    : Entity(id, pos) {this->entityType = EntityType::TRASH;}