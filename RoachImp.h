#ifndef ROACHIMP_H
#define ROACHIMP_H

#include "Roach.h"
#include "Map.h"

class RoachImp : public Roach
{
  public:
    RoachImp(int id, Cell pos, Dir dir, Antenna antenna, Type type, bool sick, Color color);
    virtual ~RoachImp();

    virtual Dir getDirection();
    virtual Antenna getAntenna();
    virtual Type getType();
    virtual bool isSick();
    virtual Color getColor();

    void doMove(Move move, Map *map);
    void alter(bool sick, Antenna antenna);
    void update(Antenna antenna, bool sick);
};

#endif /* ROACHIMP_H */
