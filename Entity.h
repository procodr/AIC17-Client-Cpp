#ifndef ENTITY_H
#define ENTITY_H

#include "Types.h"
#include "Cell.h"

class Entity
{
  protected:
    int id;
    Cell* cell;
    EntityType entityType;
    int creationTurn;

  public:
//    Entity();
    Entity(int id, Cell* cell, EntityType type);
    virtual ~Entity();

    int getId() const;
    Cell* getPosition() const;
    EntityType getType() const;

    Cell* getCell() const;

    void setPosition(int row, int col);
};

#endif /* ENTITY_H */
