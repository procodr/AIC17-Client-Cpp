#include "Game.h"
#include <ctime>
#include <x86_64-linux-gnu/sys/time.h>
#include "util.h"

long long getTimeInMilliSeconds() {
	timeval tv;
	gettimeofday(&tv,NULL);
	return (1000000 * tv.tv_sec + tv.tv_usec)/1000;
}

Game::Game()
{
	turnStartTime = -1;
	map = NULL;
	lossRate1 = 0;
	lossRate2 = 0;
	escape = 0;
	totalTurns = 0;
	turn = 0;
	turnTimeout = 0;
	myID = 0;
	firstlvl = 0;
	secondlvl = 0;
	nodeBonus = 0;
	edgeBonus = 0;
}

Game::~Game()
{
	if(map != NULL)
		delete map;
}

void Game::setConstants(Json::Value &msg) {
	this->totalTurns = msg["turns"].asInt();
	this->turnTimeout = msg["turnTimeout"].asInt();
	this->escape = msg["escape"].asInt();
	this->nodeBonus = msg["nodeBonus"].asInt();
	this->edgeBonus = msg["edgeBonus"].asInt();
	this->firstlvl = msg["firstlvl"].asInt();
	this->secondlvl = msg["secondlvl"].asInt();
	this->lossRate1 = msg["lossRate1"].asInt();
	this->lossRate2 = msg["lossRate2"].asInt();
}

int Game::getTotalTurns() {
	return this->totalTurns;
}

int Game::getEscapeConstant() {
	return this->escape;
}

int Game::getNodeBonusConstant() {
	return this->nodeBonus;
}
int Game::getEdgeBonusConstant() {
	return this->edgeBonus;
}

int Game::getLowArmyBound() {
	return this->firstlvl;
}

int Game::getMediumArmyBound() {
	return this->secondlvl;
}

double Game::getMediumCasualtyCoefficient() {
	return this->lossRate1;
}

double Game::getLowCasualtyCoefficient() {
	return this->lossRate2;
}

void Game::handleInitMessage(Message msg)
{
	Json::Value &argsArray = msg.getArray("args");

	Json::UInt I=0;
	this->myID = argsArray[I++].asInt();

	Json::Value &sizeArray = argsArray[I++];
	size = make_pair(sizeArray[0].asInt(), sizeArray[1]);

	Json::Value &fishArray = argsArray[I++];
	for(int i=0; i<fishArray.size(); i++){
		fishes.push_back(new Fish(fishArray[i][0].asInt(), fishArray[i][1].asInt(), fishArray[i][2].asInt(), fishArray[i][3].asBool(), fishArray[i][4].asBool(), fishArray[i][5].asBool(), fishArray[i][6].asBool()));
	}

	Json::Value &trashArray = argsArray[I++];
	for(int i=0; i<trashArray.size(); i++){
		trashes.push_back(new Trash(trashArray[i][0].asInt(), trashArray[i][1].asInt()));
	}

	Json::Value &netArray = argsArray[I++];
	for(int i=0; i<netArray.size(); i++){
		nets.push_back(new Net(netArray[i][0].asInt(), netArray[i][1].asInt()));
	}

	Json::Value &teleportArray = argsArray[I++];
	for(int i=0; i<teleportArray.size(); i++){
		teleports.push_back(new Net(teleportArray[i][0].asInt(), teleportArray[i][1].asInt()));
	}

	Json::Value &constants = argsArray[I++];
	this->setConstants(constants); //TODO: to be defined later

	map = new Graph(nodes);

	updateNodesList();
}

void Game::handleTurnMessage(Message msg)
{
	turnStartTime = getTimeInMilliSeconds();

	Json::Value &argsArray = msg.getArray("args");
	Json::UInt I=0;
	turn = argsArray[I++].asInt();

	Json::Value &scores = argsArray[I++];
	score = make_pair(scores[0].asInt(), scores[1].asInt());

	Json::Value &graphDiff = argsArray[I++]; //TODO: to be defined later
	// for (int i = 0; i < (int)graphDiff.size(); i++)
	// {
	// 	Json::Value &nodeDiff = graphDiff[i];
	// 	Json::UInt J=0;
	// 	int nodeIndex = nodeDiff[J++].asInt(); 
	// 	map->getNode(nodeIndex)->setOwner(nodeDiff[J++].asInt());
	// 	map->getNode(nodeIndex)->setArmyCount(nodeDiff[J++].asInt());
	// }

	updateNodesList();
}

void Game::updateNodesList()
{
	for(int i = 0; i < 3; i++)
		this->nodes[i].clear();
	for (Node* n : this->map->getNodes())
	{
		nodes[n->getOwner() + 1].push_back(n);
	}
}

long long Game::getTurnTimePassed() {
	return getTimeInMilliSeconds() - turnStartTime;
}

long long Game::getTurnRemainingTime() {
	return turnTimeout - getTurnTimePassed();
}

int Game::getMyId() {
	return myID;
}

Graph* Game::getMap() {
	return map;
}

std::vector<Node*>& Game::getMyNodes() {
	return this->nodes[this->myID + 1];
}

std::vector<Node*>& Game::getOpponentNodes() {
	return this->nodes[2 - this->myID];
}

std::vector<Node*>& Game::getFreeNodes() {
	return this->nodes[0];
}

int Game::getTurnNumber() {
	return this->turn;
}

long long Game::getTotalTurnTime() {
	return this->turnTimeout;
}

void Game::moveArmy(Node* src, Node* dst, int count)
{
	this->moveArmy(src->getIndex(), dst->getIndex(), count);
}

void Game::moveArmy(int src, int dst, int count)
{
	GameEvent* gameEvent = new GameEvent(Constants::TYPE_MOVE);
	gameEvent->addArg(src);
	gameEvent->addArg(dst);
	gameEvent->addArg(count);
	eventHandler->addEvent(gameEvent);
}
