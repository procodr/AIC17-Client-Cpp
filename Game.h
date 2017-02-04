#ifndef _GAME_H
#define _GAME_H

#include <vector>
#include <utility>

#include "World.h"
#include "Event.h"
#include "EventHandler.h"
#include "Node.h"

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

	
	pair<int, int> size;
	pair<int, int> scores;
	vector<Fish*> fishes;
	vector<Food*> foods;
	vector<Trash*> trashes;
	vector<Net*> nets;
	vector<Teleport*> teleports;

	int myID;
	int turn;
	Graph* map;
	void setConstants(Json::Value &msg);
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
