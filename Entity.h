#ifndef ENTITY_H
#define ENTITY_H

#include "Types.h"

using namespace aic;

class Entity
{
  private:
    int id;
    Cell pos;

  public:
    Entity(int id, Cell pos);
    virtual ~Entity();

    virtual int getId() const;
    virtual Cell getPos() const;
};

#endif /* ENTITY_H */
