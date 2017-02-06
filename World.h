#ifndef WORLD_H
#define WORLD_H

#include "Map.h"
#include "Types.h"
#include "Roach.h"
#include "Entity.h"

#include <vector>

using namespace aic;

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
    Entity &getEntity(int id);

    /* get a list of sewers */
    std::vector<Sewer> &getSewers();

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
    virtual void changeStrategy(Antenna t, int i, int j, int k, Move s);
    virtual void deterministicMove(const Roach &roach, Move s);
    virtual void antennaChange(const Roach &roach);

    /* get constants */
    // virtual int getTotalTurns() = 0;
};

#endif /* WORLD_H */
