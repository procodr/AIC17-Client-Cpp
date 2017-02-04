#ifndef _WORLD_H
#define _WORLD_H

#include "Graph.h"
#include "Node.h"

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
	World();
	virtual ~World();

	/**
	 * get ID of your team. it will be useful when you want to check if a node is yours or not.
	 *
	 * @return ID of your team
	 */
	virtual int getMyId() = 0;

	/**
	 * get map of the game.
	 *
	 * @return a graph that represents the map of the game.
	 */
	virtual Graph* getMap() = 0;

	/**
	 * get nodes that you are owner of them.
	 *
	 * @return your nodes
	 */
	virtual std::vector<Node*>& getMyNodes() = 0;

	/**
	 * get nodes that your opponent is owner of them.
	 *
	 * @return opponent's nodes
	 */
	virtual std::vector<Node*>& getOpponentNodes() = 0;

	/**
	 * get nodes of the game that none of the two players are owner of them.
	 *
	 * @return free (without owner) nodes
	 */
	virtual std::vector<Node*>& getFreeNodes() = 0;

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

	/**
	 * The move is the only action in this game. You can request a move by
	 * calling this method and by passing with source, destination, and number
	 * of armies you want to move from source to destination.
	 *
	 * @param src   source node
	 * @param dst   destination node
	 * @param count number of armies you want to move from source to destination
	 */
	virtual void moveArmy(Node *src, Node *dst, int count) = 0;

	/**
	 * The move is the only action in this game. You can request a move by
	 * calling this method and by passing with source, destination, and number
	 * of armies you want to move from source to destination.
	 *
	 * @param src   source node's index, you can get index of a node by calling node.getIndex().
	 * @param dst   destination node's index, you can get index of a node by calling node.getIndex().
	 * @param count number of armies you want to move from source to destination.
	 */
	virtual void moveArmy(int src, int dst, int count) = 0;

	virtual int getTotalTurns() = 0;
	virtual int getEscapeConstant() = 0;
	virtual int getNodeBonusConstant() = 0;
	virtual int getEdgeBonusConstant() = 0;
	virtual int getLowArmyBound() = 0;
	virtual int getMediumArmyBound() = 0;
	virtual double getMediumCasualtyCoefficient() = 0;
	virtual double getLowCasualtyCoefficient() = 0;

};

#endif // _WORLD_H
