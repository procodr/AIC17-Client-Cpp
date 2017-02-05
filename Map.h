#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Roach.h"
#include "Types.h"

using namespace aic;

class Map
{
  public:
	Map(std::vector<MapData*>& nodes);

    MapData *getNode(int index);
    void addItem(Item item);
    void delItem(Item item);

  private:
    std::vector< std::vector<MapData> > nodes; //0 -> Roach, 1 -> Food, 2-> Teleport
};

#endif /* MAP_H */
