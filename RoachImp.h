#ifndef ROACHIMP_H
#define ROACHIMP_H

#include "Roach.h"

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

    void update(Antenna antenna, bool sick);
};

#endif /* ROACHIMP_H */