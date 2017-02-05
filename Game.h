#ifndef GAME_H
#define GAME_H

#include <vector>
#include <utility>
#include <unordered_map>

#include "World.h"
#include "Roach.h"
#include "Event.h"
#include "EventHandler.h"
#include "Entity.h"
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

    int myID;
    Map *map;
    EntityDict entities;
    std::vector<Sewer> sewers;

    void setConstants(Json::Value &msg);

    void insertEntity(Entity entity);
    void deleteEntity(int id);
    void addSewer(Sewer sewer);

  public:
    Game();
    virtual ~Game();
    void handleInitMessage(Message msg);
    void handleTurnMessage(Message msg);

    int getTotalTurns();
    long long getTurnTimePassed();
    long long getTurnRemainingTime();

    int getMyId();
    Map &getMap();
    Entity &getEntity(int id);
    std::vector<Sewer> &getSewers();

    int getTurnNumber();
    long long getTotalTurnTime();

    void changeStrategy(Antenna t, int i, int j, int k, Move s);
    void deterministicMove(const Roach &roach, Move s);
    void antennaChange(const Roach &roach);
};

#endif /* GAME_H */