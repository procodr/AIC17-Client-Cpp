#include "Sewer.h"

Sewer::Sewer(int id, Cell pos, int destId) : Entity(id, pos), destId(destId) {};

int Sewer::getDestId()
{
    return destId;
}
