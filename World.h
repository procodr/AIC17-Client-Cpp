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

    /**
     *
     * @param id Roach id
     * @return get Entity object by id. You can cast it to wanted types.
     */
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
    /**
     * Changing the strategy of the roachs with the given antenna type
     *
     * @param t Antenna type of the roach (0 for single antenna and 1 for double antenna)
     * @param left Condition of the top-left neighbour
     * @param right Condition of the top-right neighbour
     * @param front Condition of the front
     * @param s The command given to the roach (You can check Move in types)
     */
    virtual void changeStrategy(Antenna t, int left, int right, int front, Move s) = 0;
    

    /**
     * Give command to a specific Beetle with the given id
     *
     * @param id Beetle id
     * @param s The command given to the roach of Move type
     */
    virtual void deterministicMove(Roach &roach, Move s) = 0;

    /**
     * Changes antenna type of the given roach
     *
     * @param roach Roach type
     * @param c Antenna type
     */
    virtual void antennaChange(Roach &roach, Antenna c) = 0;

    /* get constants */

    /**
     *
     * @return Maximum amount of turns
     */
    virtual int getTurnTimeout() const = 0;

    /**
     * Probability of a food showing up in any of the tiles without content(Roach or Food)
     *
     * @return Food probability
     */
    virtual double getFoodProb() const = 0;

    /**
     * Probability of a trash showing up in any of the tiles without content(Roach or Food)
     *
     * @return Trash probability
     */
    virtual double getTrashProb() const = 0;

    /**
     * Probability of a net showing up in any of the tiles without a net
     *
     * @return Net probability
     */
    virtual double getNetProb() const = 0;

    virtual int getNetValidTime() const = 0;

    /**
     * Cost of changing the antenna of a roach
     *
     * @return Antenna cost
     */
    virtual int getColorCost() const = 0;

    /**
     * Sick roachs give points to the opposing team of all their 8 neighbours
     *
     * @return Given points for each neighbour
     */
    virtual int getSickCost() const = 0;

    /**
     *
     * @return Cost of changing strategy
     */
    virtual int getUpdateCost() const = 0;

    /**
     *
     * @return Cost of a deterministic move
     */
    virtual int getDetMoveCost() const = 0;

    /**
     *
     * @return Points achieved when a normal roach kills a queen
     */
    virtual int getKillQueenScore() const = 0;

    /**
     *
     * @return Points achieved when two queens kill each other
     */
    virtual int getKillBothQueenScore() const = 0;

    /**
     *
     * @return Points achieved from killing a normal roach
     */
    virtual int getKillFishScore() const = 0;

    virtual int getQueenCollisionScore() const = 0;

    /**
     *
     * @return Points achieved when a normal roach consumes food
     */
    virtual int getFishFoodScore() const = 0;

    /**
     *
     * @return Points achieved when a queen roach consumes food
     */
    virtual int getQueenFoodScore() const = 0;

    /**
     *
     * @return Beetle's lifespan since getting sick
     */
    virtual int getSickLifeTime() const = 0;
    /**
     *
     * @return Amount of power that a roach achieves each turn
     */
    virtual double getPowerRatio() const = 0;

    /**
     * If the map is "end ratio" percent full, the game ends
     *
     * @return End ratio
     */
    virtual double getEndRatio() const = 0;

    /**
     *
     * @return Minimum roach population required for a roach to disobey
     */
    virtual int getDisobeyNum() const = 0;

    /**
     *
     * @return Amount of turns a food stays on the map
     */
    virtual int getFoodValidTime() const = 0;

    /**
     *
     * @return Amount of turns a trash stays on the map
     */
    virtual int getTrashValidTime() const = 0;


//    /**
//     *
//     * @return Team id
//     */
//    int getTeamID();
//
//    /**
//     *
//     * @return width
//     */
//    int getWidth();
//
//    /**
//     *
//     * @return height
//     */
//    int getHeight();
//
//    /**
//     *
//     * @return User's score
//     */
//    int getMyScore();
//
//    /**
//     *
//     * @return Opponent's score
//     */
//    int getOppScore();
//
//    /**
//     *
//     * @return Tiles which contains user's beetles
//     */
//    Tile[] getMyTiles();
//
//    /**
//     *
//     * @return Tiles which contains opponent's beetles
//     */
//    Tile[] getOppTiles();
//
//    /**
//     *
//     * @return Tiles which contains Teleporting devices
//     */
//    Tile[] getTeleportTiles();
//
//    /**
//     *
//     * @return Tiles which contains net
//     */
//    Tile[] getNetTiles();
//
//    /**
//     *
//     * @return Tiles which contains trash
//     */
//    Tile[] getTrashTiles();
//
//    /**
//     *
//     * @return Tiles which contains food
//     */
//    Tile[] getFoodTiles();

};

#endif /* WORLD_H */
