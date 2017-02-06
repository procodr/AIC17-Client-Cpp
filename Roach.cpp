#include "Roach.h"

Roach::Roach(int id, Cell pos, Dir dir, Antenna antenna, Type type, bool sick, Color color)
    : Entity(id, pos), dir(dir), antenna(antenna), type(type), sick(sick), color(color) {};
