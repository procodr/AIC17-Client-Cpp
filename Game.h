#ifndef GAME_H
#define GAME_H

#include <vector>
#include <utility>
#include <map>

#include "World.h"
#include "Roach.h"
#include "Event.h"
#include "EventHandler.h"
#include "Item.h"
#include "Types.h"
#include "Map.h"

using namespace aic;

/**
 * Model contains data which describes current state of the game.
 * You do not need to read this class, it's internal implementation.
 * See World interface for more information.
 * Do not change this class.
 */

class Game : public World
{
  private:
    int turn;
    int totalTurns;
    long long turnTimeout;
    long long turnStartTime;

    std::pair<int, int> score;
    std::map<int, &Item> itemDictionary;

    int myID;
	Map *map;
    // Size size;
    // std::vector<Roach *> roaches;
    // std::vector<Item> food;
    // std::vector<Item> trashes;
    // std::vector<Item> slippers;
    // std::vector<Teleport> teleports;

    void setConstants(Json::Value &msg);
    
    //dictionary functions
    void addToDictionary(Item item);
    Item findInDictionary(int id);

  public:
    Game();
    virtual ~Game();
    void handleInitMessage(Message msg);
    void handleTurnMessage(Message msg);

    int getTotalTurns();
    long long getTurnTimePassed();
    long long getTurnRemainingTime();

    int getMyId();
    // Size getSize();
    // std::vector<Roach *> &getRoaches();
    // std::vector<Item> &getFood();
    // std::vector<Item> &getTrash();
    // std::vector<Item> &getSlippers();
    // std::vector<Teleport> &getTeleports();
	Map &getMap();

    void changeStrategy(Antenna t, int i, int j, int k, Move s);
    void deterministicMove(const Roach &roach, Move s);
    void antennaChange(const Roach &roach);


};

#endif
/* GAME_H */
