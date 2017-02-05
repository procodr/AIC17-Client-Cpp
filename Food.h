#ifndef FOOD_H
#define FOOD_H

#include <utility>
#include "Types.h"

using namespace aic;

class Food : public Item
{
  public:
    Food(int id, Cell pos);
};

#endif /* FOOD_H */
