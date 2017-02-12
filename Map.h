#ifndef MAP_H
#define MAP_H

#include "Types.h"
#include "Cell.h"

#include <map>
#include <vector>

class Map
{
  public:
	Map(Size size, int myId);

    virtual ~Map();

    int getWidth();

    int getHeight();

    std::vector<Cell*> getMyCells();

    std::vector<Cell*> getOppCells();

    std::vector<Cell*> getTeleportCells();

    std::vector<Cell*> getSlipperCells();

    std::vector<Cell*> getTrashCells();

    std::vector<Cell*> getFoodCells();

    Entity *getEntity(int id);

    EntityType getEntityType(int id);

    void addEntity(Entity *entity);

    void moveEntity(int id, Move move);
    void moveEntity(int id, int row, int col, bool wing, bool sick);

    void delEntity(int id);
private:
    Size size;
    int myId;
//    Cell*** table;
    std::map<int, Entity *> allEntities;
    std::vector<Cell *> myCells;
    std::vector<Cell *> oppCells;
    std::vector<Cell *> teleportCells;
    std::vector<Cell *> slipperCells;
    std::vector<Cell *> trashCells;
    std::vector<Cell *> foodCells;
};

#endif /* MAP_H */
