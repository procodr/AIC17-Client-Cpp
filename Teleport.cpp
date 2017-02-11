#include "Teleport.h"

Teleport::Teleport(int id, Cell pos, int destId) : Entity(id, pos, EntityType::TELEPORT), destId(destId) {
}

int Teleport::getDestId()
{
    return destId;
}
