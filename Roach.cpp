#include "Roach.h"

Roach::Roach(int id, Cell pos, Dir dir, Antenna antenna, Type type, bool sick, Color color)
    : Entity(id, pos), dir(dir), antenna(antenna), type(type), sick(sick), color(color) {};

Roach::~Roach() {}

Color Roach::getColor()
{
    return this->color;
}

Antenna Roach::getAntenna()
{
    return this->antenna;
}

Type Roach::getType()
{
    return this->type;
}

Dir Roach::getDirection()
{
    return this->dir;
}

bool Roach::isSick()
{
    return this->sick;
}

void Roach::update(Antenna antenna, bool sick)
{
    this->antenna = antenna;
    this->sick = sick;
}
