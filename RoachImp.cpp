#include "RoachImp.h"

RoachImp::RoachImp(int id, Cell pos, Dir dir, Antenna antenna, Type type, bool sick, Color color)
    : Roach(id, pos, dir, antenna, type, sick, color) {}

RoachImp::~RoachImp() {}

Color RoachImp::getColor()
{
    return this->color;
}

Antenna RoachImp::getAntenna()
{
    return this->antenna;
}

Type RoachImp::getType()
{
    return this->type;
}

Dir RoachImp::getDirection()
{
    return this->dir;
}

bool RoachImp::isSick()
{
    return this->sick;
}

void RoachImp::update(Antenna antenna, bool sick)
{
    this->antenna = antenna;
    this->sick = sick;
}
