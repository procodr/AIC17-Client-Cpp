#ifndef ENTITY_H
#define ENTITY_H

#include "Types.h"
#include "Cell.h"

class Entity
{
  protected:
    int id;
    Cell pos;
    EntityType entityType;
    int team_id;

  public:
    Entity();
    Entity(int id, Cell pos);
    virtual ~Entity();

    int getId() const;
    Cell getPosition() const;
    EntityType getType() const;
    int getTeamId() const;

};

#endif /* ENTITY_H */
