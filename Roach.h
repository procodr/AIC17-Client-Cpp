#ifndef ROACH_H
#define ROACH_H

#include <utility>
#include "Types.h"

using namespace aic;

class Roach : public Item
{
  public:
    Roach(int id, Cell pos, Dir dir, Antenna antenna, Type type, bool sick, Color color);

	Dir getDirection();
    Antenna getAntenna();
    Type getType();
    bool isSick();
    Color getColor();
    
  private:
    Dir dir;
    Antenna antenna;
    Type type;
    bool sick;
	Color color;
};

#endif /* ROACH_H */