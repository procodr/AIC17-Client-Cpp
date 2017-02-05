#ifndef TRASH_H
#define TRASH_H

#include <utility>
#include "Types.h"

using namespace aic;

class Trash : public Item
{
  public:
    Trash(int id, Cell pos);
};

#endif /* TRASH_H */
