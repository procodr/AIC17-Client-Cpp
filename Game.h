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
#include "jsoncpp-src-0.5.0/include/json/json.h"

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
    MapImp *map;
    EntityDict entities;

    int turnTimeout;
    double foodProb;
    double trashProb;
    double netProb;
    int netValidTime;
    int colorCost;
    int sickCost;
    int updateCost;
    int detMoveCost;
    int killQueenScore;
    int killBothQueenScore;
    int killFishScore;
    int queenCollisionScore;
    int fishFoodScore;
    int queenFoodScore;
    int sickLifeTime;
    double powerRatio;
    double endRatio;
    int disobeyNum;
    int foodValidTime;
    int trashValidTime;

    void setConstants(Json::Value &msg);

    void insertEntity(Entity* entity);

    void deleteEntity(int id);

    void moveEntity(int id, int x, int y);

public:
    Game();

    virtual ~Game();

    virtual int getMyId();

    virtual MapImp &getMap();

    virtual Entity* getEntity(int id);

    virtual int getTurnNumber();

    virtual long long getTotalTurnTime();

    virtual long long getTurnTimePassed();

    virtual long long getTurnRemainingTime();

    virtual void changeStrategy(Antenna t, int left, int right, int front, Move s);

    virtual void deterministicMove(const Roach &roach, Move s);

    virtual void antennaChange(const Roach &roach, Antenna c);

    void handleInitMessage(Message msg);

    void handleTurnMessage(Message msg);

    int getTurnTimeout() const;

    double getFoodProb() const;

    double getTrashProb() const;

    double getNetProb() const;

    int getNetValidTime() const;

    int getColorCost() const;

    int getSickCost() const;

    int getUpdateCost() const;

    int getDetMoveCost() const;

    int getKillQueenScore() const;

    int getKillBothQueenScore() const;

    int getKillFishScore() const;

    int getQueenCollisionScore() const;

    int getFishFoodScore() const;

    int getQueenFoodScore() const;

    int getSickLifeTime() const;

    double getPowerRatio() const;

    double getEndRatio() const;

    int getDisobeyNum() const;

    int getFoodValidTime() const;

    int getTrashValidTime() const;
};

#endif /* GAME_H */
