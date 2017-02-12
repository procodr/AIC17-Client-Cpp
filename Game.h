#ifndef GAME_H
#define GAME_H

#include <vector>
#include <utility>
#include <unordered_map>

#include "Cell.h"
#include "World.h"
#include "Event.h"
#include "EventHandler.h"
#include "Entity.h"
#include "Types.h"
#include "Map.h"
#include "Constants.h"

/**
 * Model contains data which describes current state of the game.
 * You do not need to read this class, it's internal implementation.
 * See World interface for more information.
 * Do not change this class.
 */

class Game : public World {
private:
    int turn;
    int totalTurns;
    long long turnStartTime;

    std::pair<int, int> score;

    int myID;
    Map *map;
//    EntityDict entities;
//    EntityDict opp_entities;

    Constants constants;

    int turnTimeout;

    void setConstants(Json::Value &msg);

//    void insertEntity(Entity* entity);
//
//    void deleteEntity(int id);

//    void moveEntity(int id, int x, int y);

public:
    Game();

    virtual ~Game();

    virtual void changeStrategy(bool wing, CellState left, CellState right, CellState front, Move strategy);

    virtual void deterministicMove(Beetle &roach, Move strategy);

    virtual void changeType(Beetle &roach, bool wing);

    virtual int getCurrentTurn();

    virtual int getTotalTurns();

    virtual long long getTurnRemainingTime();

    virtual long long getTurnTotalTime();

    virtual int getTeamId();

    virtual int getMyScore();

    virtual int getOppScore();

    Constants getConstants() const;

    virtual Map* getMap();

    long long getTurnTimePassed();

    void handleInitMessage(Message &msg);

    void handleTurnMessage(Message &msg);
};

#endif /* GAME_H */
