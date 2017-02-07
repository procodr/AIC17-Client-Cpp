#ifndef MAP_H
#define MAP_H

#include "Roach.h"
#include "Types.h"

#include <vector>

using namespace aic;

class Map
{
  public:
    virtual ~Map() {};

    virtual Size getSize() const = 0;
    virtual Entity *getEntity(int x, int y) = 0;
    virtual bool getShadow(int x, int y) = 0;
    virtual Cell getDest(int x, int y) = 0;
};

#endif /* MAP_H */
