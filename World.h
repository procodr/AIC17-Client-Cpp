#ifndef WORLD_H
#define WORLD_H

#include "Constants.h"
#include "Map.h"
#include "Types.h"
#include "Entity.h"

#include <vector>

#include "Beetle.h"
#include "Teleport.h"

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

    /* game moves */
    /**
     * Changing the strategy of the roachs with the given antenna type
     *
     * @param t Antenna type of the roach (0 for single antenna and 1 for double antenna)
     * @param left Condition of the top-left neighbour
     * @param right Condition of the top-right neighbour
     * @param front Condition of the front
     * @param s The command given to the roach (You can check Move in types)
     */
    virtual void changeStrategy(bool wing, CellState left, CellState right, CellState front, Move strategy) = 0;


    /**
     * Give command to a specific Beetle with the given id
     *
     * @param id Beetle id
     * @param s The command given to the roach of Move type
     */
    virtual void deterministicMove(Beetle &roach, Move strategy) = 0;

    /**
     * Changes antenna type of the given roach
     *
     * @param roach Roach type
     * @param c Antenna type
     */
    virtual void changeType(Beetle &roach, bool wing) = 0;

    /**
	 * number of turns that passed as long as game started.
	 *
	 * @return turn number
	 */
    virtual int getCurrentTurn() = 0;

    /**
	 *
	 * @return Amount of all turns
	 */
	virtual int getTotalTurns() = 0;

    /**
	 * get the remaining time of the current turn.
	 *
	 * @return turn remaining time (ms)
	 */
    virtual long long getTurnRemainingTime() = 0;

    /**
	 * get time limit of each turn.
	 *
	 * @return total turn time (ms)
	 */
    virtual long long getTurnTotalTime() = 0;

    /**
	 * get ID of your team. it will be useful when you want to check if a node is yours or not.
	 *
	 * @return ID of your team
	 */
    virtual int getTeamId() = 0;

	/**
	 *
	 * @return get score of team
	 */
	virtual int getMyScore() = 0;

	/**
	 *
	 * @return get score of opponent team
	 */
	virtual int getOppScore() = 0;

	/**
	 *
	 * @return get constants
	 */
	virtual Constants getConstants() const = 0;

	/**
	 * get map of the game.
	 *
	 * @return a Map that represents the game board.
	 */
    virtual Map* getMap() = 0;
};

#endif /* WORLD_H */
