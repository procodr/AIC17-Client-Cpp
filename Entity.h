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
    int creationTurn;

  public:
//    Entity();
    Entity(int id, Cell pos, EntityType type);
    virtual ~Entity();

    int getId() const;
    Cell getPosition() const;
    EntityType getType() const;
};

#endif /* ENTITY_H */
