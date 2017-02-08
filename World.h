#ifndef WORLD_H
#define WORLD_H

#include "Map.h"
#include "Types.h"
#include "Sewer.h"
#include "Roach.h"
#include "Entity.h"

#include <vector>

/**
 * Game Interface
 * At each turn, you are given an instance of the World, and you can call any of
 * the following methods to get information from the game, or do action on the
 * game. Please read documentation of any method you have problem with that.
 * Please do not change this class.
 */
class World
{
  public:
    virtual ~World() {};

    /**
	 * get ID of your team. it will be useful when you want to check if a node is yours or not.
	 *
	 * @return ID of your team
	 */
    virtual int getMyId() = 0;

    /**
	 * get map of the game.
	 *
	 * @return a Map that represents the game board.
	 */
    virtual Map &getMap() = 0;

    /* get entity by id */
    virtual Entity* getEntity(int id) = 0;

    /**
	 * number of turns that passed as long as game started.
	 *
	 * @return turn number
	 */
    virtual int getTurnNumber() = 0;

    /**
	 * get time limit of each turn.
	 *
	 * @return total turn time (ms)
	 */
    virtual long long getTotalTurnTime() = 0;

    /**
	 * get time passed from when the last turn is started.
	 *
	 * @return turn time passed (ms)
	 */
    virtual long long getTurnTimePassed() = 0;

    /**
	 * get the remaining time of the current turn.
	 *
	 * @return turn remaining time (ms)
	 */
    virtual long long getTurnRemainingTime() = 0;

    /* game moves */
    virtual void changeStrategy(Antenna t, int left, int right, int front, Move s) = 0;
    virtual void deterministicMove(const Roach &roach, Move s) = 0;
    virtual void antennaChange(const Roach &roach, Antenna c) = 0;

    /* get constants */
    virtual int getTurnTimeout() const = 0;

    virtual double getFoodProb() const = 0;

    virtual double getTrashProb() const = 0;

    virtual double getNetProb() const = 0;

    virtual int getNetValidTime() const = 0;

    virtual int getColorCost() const = 0;

    virtual int getSickCost() const = 0;

    virtual int getUpdateCost() const = 0;

    virtual int getDetMoveCost() const = 0;

    virtual int getKillQueenScore() const = 0;

    virtual int getKillBothQueenScore() const = 0;

    virtual int getKillFishScore() const = 0;

    virtual int getQueenCollisionScore() const = 0;

    virtual int getFishFoodScore() const = 0;

    virtual int getQueenFoodScore() const = 0;

    virtual int getSickLifeTime() const = 0;

    virtual double getPowerRatio() const = 0;

    virtual double getEndRatio() const = 0;

    virtual int getDisobeyNum() const = 0;

    virtual int getFoodValidTime() const = 0;

    virtual int getTrashValidTime() const = 0;
};

#endif /* WORLD_H */
