#ifndef TELEPORT_H
#define TELEPORT_H

#include <utility>
#include "Types.h"

using namespace aic;

class Teleport : public Item
{
  private:
    Cell dest;
    
  public:
    Teleport(int id, Cell pos);
    Cell getDestination();
};

#endif /* TELEPORT_H */
