#ifndef ROACH_H
#define ROACH_H

#include "Types.h"
#include "Entity.h"

#include <utility>

using namespace aic;

class Roach : public Entity
{
  public:
    Roach(int id, Cell pos, Dir dir, Antenna antenna, Type type, bool sick, Color color);
    virtual ~Roach() {};

    /* Use these to get information about your fellow cockroaches! */
    virtual Dir getDirection() = 0;
    virtual Antenna getAntenna() = 0;
    virtual Type getType() = 0;
    virtual bool isSick() = 0;
    virtual Color getColor() = 0;

  protected:
    Dir dir;
    Antenna antenna;
    Type type;
    bool sick;
    Color color;
};

#endif /* ROACH_H */