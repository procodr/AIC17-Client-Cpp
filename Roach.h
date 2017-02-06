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
    virtual ~Roach();

    /* Use these to get information about your fellow cockroaches! */
    Dir getDirection();
    Antenna getAntenna();
    Type getType();
    bool isSick();
    Color getColor();

    /* The server calls these methods. Don't worry about them. */
    void update(Antenna antenna, bool sick);

  private:
    Dir dir;
    Antenna antenna;
    Type type;
    bool sick;
    Color color;
};

#endif /* ROACH_H */