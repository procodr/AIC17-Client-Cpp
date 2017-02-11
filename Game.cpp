#include "Entity.h"
#include "Game.h"
#include "Slippers.h"
#include "Trash.h"
#include "Food.h"
#include "util.h"

#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else

#include <sys/time.h>

#endif

long long getTimeInMilliSeconds() {
#ifdef _WIN32
	SYSTEMTIME tv;
	GetSystemTime(&tv);
	return tv.wSecond * 1000 + tv.wMilliseconds;
#else
	timeval tv;
	gettimeofday(&tv, NULL);
	return 1000 * tv.tv_sec + tv.tv_usec / 1000;
#endif
}

Game::Game() {
	turn = 0;
	totalTurns = 0;
	turnTimeout = 0;
	turnStartTime = -1;

	myID = 0;

	map = NULL;
}

Game::~Game() {
	delete map;
}

void Game::changeStrategy(bool wing, CellState left, CellState right, CellState front, Move strategy) {
	GameEvent *ev = new GameEvent(Constants::TYPE_CHANGE_STRATEGY);
	ev->addArg(wing);
	ev->addArg(static_cast<int>(right));
	ev->addArg(static_cast<int>(front));
	ev->addArg(static_cast<int>(left));
	ev->addArg(static_cast<int>(strategy));
	eventHandler->addEvent(ev);
}

void Game::deterministicMove(Beetle &beetle, Move strategy) {
	GameEvent *ev = new GameEvent(Constants::TYPE_DETERMINISTIC_MOVE);
	ev->addArg(beetle.getId());
	ev->addArg(static_cast<int>(strategy));
	eventHandler->addEvent(ev);
}

void Game::changeType(Beetle &beetle, bool wing) {
	GameEvent *ev = new GameEvent(Constants::TYPE_ANTENNA_CHANGE);
	ev->addArg(beetle.getId());
	ev->addArg(wing);
	eventHandler->addEvent(ev);
}

int Game::getCurrentTurn() {
	return this->turn;
}

int Game::getTotalTurns() {
	return this->totalTurns;
}

long long Game::getTurnRemainingTime() {
	return turnTimeout - getTurnTimePassed();
}

long long Game::getTurnTotalTime() {
	return this->turnTimeout;
}

int Game::getTeamId() {
	return myID;
}

int Game::getMyScore() {
	if(this->getTeamId() == 0)
		return score.first;
	else
		return score.second;
}

int Game::getOppScore() {
	if(this->getTeamId() == 0)
		return score.second;
	else
		return score.first;
}

Constants Game::getConstants() const {
	return this->constants;
}

Map* Game::getMap() {
	return map;
}

void Game::setConstants(Json::Value &msg) {
	this->turnTimeout = msg[0u].asInt();
	constants.setConstants(msg);
	this->totalTurns = msg[21u].asInt();
}

long long Game::getTurnTimePassed() {
	return getTimeInMilliSeconds() - turnStartTime;
}

void Game::handleInitMessage(Message &msg) {
	Json::Value &argsArray = msg.getArray("args");

	Json::UInt I = 0;

	this->myID = argsArray[I++].asInt();

	Json::Value &sizeArray = argsArray[I++];
	Size size = { sizeArray[0u].asInt(), sizeArray[1u].asInt() };
	map = new Map(size, myID);

	Json::Value &roachArray = argsArray[I++];

	for (Json::UInt i = 0; i < roachArray.size(); i++) {
		CERR("Beetle " << roachArray[i][0u].asInt() << " at\t" << roachArray[i][1u].asInt() << ", " << roachArray[i][2u].asInt() << "\n");
		map->addEntity(
				new Beetle(roachArray[i][0u].asInt(),
						{ roachArray[i][1u].asInt(), roachArray[i][2u].asInt() },
						static_cast<Direction>(roachArray[i][3u].asInt()),
						roachArray[i][4u].asBool(),
						static_cast<BeetleType>(roachArray[i][5u].asInt()),
						roachArray[i][6u].asBool(),
						roachArray[i][7u].asInt()));
	}

	Json::Value &foodArray = argsArray[I++];
	for (int i = 0; i < (int) foodArray.size(); i++) {
		CERR("Food  at\t" << roachArray[i][1u].asInt() << ", " << roachArray[i][2u].asInt() << "\n");
		map->addEntity(
				new Food(foodArray[i][0u].asInt(), { foodArray[i][1u].asInt(),
						foodArray[i][2u].asInt() }));
	}

	Json::Value &trashArray = argsArray[I++];
	for (int i = 0; i < (int) trashArray.size(); i++) {
		CERR("Trash at\t" << roachArray[i][1u].asInt() << ", " << roachArray[i][2u].asInt() << "\n");
		map->addEntity(new Trash(trashArray[i][0u].asInt(), {
				trashArray[i][1u].asInt(), trashArray[i][2u].asInt() }));
	}

	Json::Value &slippersArray = argsArray[I++];
	for (int i = 0; i < (int) slippersArray.size(); i++) {
		CERR("Slipp at\t" << roachArray[i][1u].asInt() << ", " << roachArray[i][2u].asInt() << "\n");
		map->addEntity(new Slippers(slippersArray[i][0u].asInt(), {
				slippersArray[i][1u].asInt(), slippersArray[i][2u].asInt() }));
	}

	Json::Value &sewerArray = argsArray[I++];
	for (int i = 0; i < (int) sewerArray.size(); i++) {
		CERR("Sewer at\t" << roachArray[i][1u].asInt() << ", " << roachArray[i][2u].asInt() << "\n");
		map->addEntity(
				new Teleport(sewerArray[i][0u].asInt(), {
						sewerArray[i][1u].asInt(), sewerArray[i][2u].asInt() },
						sewerArray[i][3u].asInt()));
	}

	Json::Value &constants = argsArray[I++];
	this->setConstants(constants);
}

void Game::handleTurnMessage(Message &msg) {
	turnStartTime = getTimeInMilliSeconds();

	Json::Value &argsArray = msg.getArray("args");

	Json::UInt I = 0;

	turn = argsArray[I++].asInt();
	CERR("Turn: " << turn << "\n");

	Json::Value &scores = argsArray[I++];
	score = std::make_pair(scores[0u].asInt(), scores[1u].asInt());

	Json::Value &changesArray = argsArray[I++];
	for (int i = 0; i < (int) changesArray.size(); i++) {
		Json::Value &change = changesArray[i];
		Json::Value &changeArgs = change["args"];

		std::string changeType = change["type"].asString();
		for (int j = 0; j < (int) changeArgs.size(); j++) {
			Json::UInt I = 0;
			Json::Value &singleChange = changeArgs[j];

			if (changeType == "a") {
				/* add */
				int id = singleChange[I++].asInt();
				EntityType type = static_cast<EntityType>(singleChange[I++].asInt());
				int row = singleChange[I++].asInt();
				int col = singleChange[I++].asInt();
				Cell pos(row, col);

				if (type == EntityType::BEETLE) {
					Direction dir = static_cast<Direction>(singleChange[I++].asInt());
					bool wing = singleChange[I++].asBool();
					BeetleType type = static_cast<BeetleType>(singleChange[I++].asInt());
					bool sick = singleChange[I++].asBool();
					int team_id = singleChange[I++].asInt();
					map->addEntity(new Beetle(id, pos, dir, wing, type, sick, team_id));
				} else if (type == EntityType::FOOD) {
					map->addEntity(new Food(id, pos));
				} else if (type == EntityType::SLIPPERS) {
					map->addEntity(new Slippers(id, pos));
				} else if (type == EntityType::TRASH) {
					map->addEntity(new Trash(id, pos));
				} else {
					throw("unknown entity type");
				}

			} else if (changeType == "d") {
				/* delete */
				int id = singleChange[I++].asInt();

				map->delEntity(id);

			} else if (changeType == "m") {
				/* move */
				int id = singleChange[I++].asInt();
				Move move = static_cast<Move>(singleChange[1u].asInt());

				map->moveEntity(id, move);

			} else if (changeType == "c") {
				/* alter */
				int id = singleChange[I++].asInt();

				int x = singleChange[I++].asInt();
				int y = singleChange[I++].asInt();
				bool wing = singleChange[I++].asBool();
				bool sick = singleChange[I++].asBool();
				map->moveEntity(id, x, y, wing, sick);
			} else {
				/* error */
				throw("unknown change type");
			}
		}
	}
}
