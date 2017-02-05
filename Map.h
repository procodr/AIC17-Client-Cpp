#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Roach.h"
#include "Types.h"

using namespace aic;

class Map
{
  public:
    Map(Size size);

    Entity *getEntity(int x, int y);
    bool getShadow(int x, int y);
    Cell getDest(int x, int y);
    
    void addEntity(const Entity &entity);
    void delEntity(int x, int y);
    
    void addShadow(int x, int y);
    void delShadow(int x, int y);
    
    void addTeleport(Teleport teleport);

  private:
    Size size;
    std::vector< std::vector<Entity *> > entityMap;
    std::vector< std::vector<int> > darknessMap;
    std::vector< std::vector<Cell> > destMap;

    void changeShadow(int x, int y, int delta);
};

#endif /* MAP_H */
