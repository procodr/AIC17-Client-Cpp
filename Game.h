#ifndef _GAME_H
#define _GAME_H

#include <vector>
#include <utility>

#include "World.h"
#include "Fish.h"
#include "Event.h"
#include "EventHandler.h"
#include "Node.h"
#include "Types.h"

/**
 * Model contains data which describes current state of the game.
 * You do not need to read this class, it's internal implementation.
 * See World interface for more information.
 * Do not change this class.
 */


class Game : public World
{
private:
	int totalTurns;
	long long turnTimeout;
	long long turnStartTime;

	
	std::pair<int, int> size;
	std::pair<int, int> score;
	std::vector< Fish* > fishes;
	std::vector< Cell > foods;
	std::vector< Cell > trashes;
	std::vector< Cell > nets;
	std::vector< Teleport > teleports;

	int myID;
	int turn;
	Graph* map;
	void setConstants(Json::Value &msg);

	int escape;//TODO: to be deleted
	int nodeBonus;
	int edgeBonus;
	int firstlvl;
	int secondlvl;
	double lossRate1;
	double lossRate2;

	std::vector<Node*> nodes[3];
public:
	Game();
	virtual ~Game();
	void handleInitMessage(Message msg);
	void handleTurnMessage(Message msg);
	void updateNodesList();
	int getTotalTurns();
	long long getTurnTimePassed();
	long long getTurnRemainingTime();

	int getEscapeConstant();
	int getNodeBonusConstant();
	int getEdgeBonusConstant();
	int getLowArmyBound();
	int getMediumArmyBound();
	double getMediumCasualtyCoefficient();
	double getLowCasualtyCoefficient();

	int getMyId();
	Graph* getMap();
	std::vector<Node*>& getMyNodes();
	std::vector<Node*>& getOpponentNodes();
	std::vector<Node*>& getFreeNodes();
	int getTurnNumber();
	long long getTotalTurnTime();
	void moveArmy(Node* src, Node* dst, int count);
	void moveArmy(int src, int dst, int count);
};

#endif // _GAME_H
