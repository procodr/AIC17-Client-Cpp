#include "Roach.h"

Roach::Roach(int id, Cell pos, Dir dir, Team team, Type type, bool sick, Color color)
    : id(id), pos(pos), dir(dir), color(color), type(type), sick(sick), team(team) {};

int Roach::getId()
{
    return this->id;
}

Cell Roach::getPos()
{
    return this->pos;
}

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
