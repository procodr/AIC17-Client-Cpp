#ifndef GAME_H
#define GAME_H

#include <vector>
#include <utility>
#include <unordered_map>

#include "World.h"
#include "RoachImp.h"
#include "Event.h"
#include "EventHandler.h"
#include "Entity.h"
#include "Types.h"
#include "MapImp.h"

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
    MapImp *map;
    EntityDict entities;
    std::vector<Sewer> sewers;

    void setConstants(Json::Value &msg);

    void insertEntity(Entity entity);
    void deleteEntity(int id);
    void addSewer(Sewer sewer);

  public:
    Game();
    virtual ~Game();

    virtual int getMyId();
    virtual MapImp &getMap();
    virtual Entity &getEntity(int id);
    virtual std::vector<Sewer> &getSewers();

    virtual int getTurnNumber();
    virtual long long getTotalTurnTime();
    virtual long long getTurnTimePassed();
    virtual long long getTurnRemainingTime();

    virtual void changeStrategy(Antenna t, int i, int j, int k, Move s);
    virtual void deterministicMove(const Roach &roach, Move s);
    virtual void antennaChange(const Roach &roach);

    void handleInitMessage(Message msg);
    void handleTurnMessage(Message msg);
};

#endif /* GAME_H */