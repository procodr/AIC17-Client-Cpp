#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Roach.h"
#include "Types.h"

using namespace aic;

class Map
{
  public:
	Map(std::vector<Node *> &nodes);

    std::vector<Node *> &getNodes();

    Node *getNode(int index);

  private:
    std::vector<Node *> nodes;
};

#endif /* MAP_H */
