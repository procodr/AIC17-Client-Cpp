#include "Teleport.h"

Teleport::Teleport(int id, Cell pos, int destId) : Entity(id, pos), destId(destId) {this->entityType = EntityType::TELEPORT;};

int Teleport::getDestId()
{
    return destId;
}
