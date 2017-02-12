#ifndef BEETLE_H
#define BEETLE_H

#include "Types.h"
#include "Entity.h"

#include <utility>

class Beetle : public Entity
{
  public:
    Beetle(int id, Cell* pos, Direction dir, bool wing, BeetleType beetle_type, bool sick, int team_id);
    virtual ~Beetle() {};

    /* Use these to get information about your fellow cockroaches! */
    int getRow();
    int getColumn();
    Direction getDirection();
    BeetleType getBeetleType();
    bool has_wing();
    bool is_sick();
    int getTeamId();
    
    void setSick(bool sick);
    void setWing(bool wing);

    void doMove(Move move, Size size);
    void alter(bool sick, bool wing);

  protected:
    Direction dir;
    bool wing;
    bool sick;
    BeetleType beetle_type;
    int team_id;
};

#endif /* BEETLE_H */
