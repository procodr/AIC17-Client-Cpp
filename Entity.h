#ifndef ENTITY_H
#define ENTITY_H

#include "Types.h"

class Entity
{
  protected:
    int id;
    Cell pos;
    EntityType entityType;

  public:
    Entity();
    Entity(int id, Cell pos);
    virtual ~Entity();

    virtual int getId() const;
    virtual Cell getPos() const;
    virtual EntityType getEntityType() const;

    virtual void doMove(int x, int y);
};

#endif /* ENTITY_H */
