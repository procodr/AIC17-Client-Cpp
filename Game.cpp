#include "Entity.h"
#include "Game.h"
#include "Teleport.h"
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

	Json::Value &beetleArray = argsArray[I++];

	for (Json::UInt i = 0; i < beetleArray.size(); i++) {
		CERR("Beetle " << beetleArray[i][0u].asInt() << " at\t" << beetleArray[i][1u].asInt() << ", " << beetleArray[i][2u].asInt() << "\n");
		map->addEntity(
				new Beetle(beetleArray[i][0u].asInt(),
						new Cell(beetleArray[i][1u].asInt(), beetleArray[i][2u].asInt()),
						static_cast<Direction>(beetleArray[i][3u].asInt()),
						beetleArray[i][4u].asBool(),
						static_cast<BeetleType>(beetleArray[i][5u].asInt()),
						beetleArray[i][6u].asBool(),
						beetleArray[i][7u].asInt()));
	}

	Json::Value &foodArray = argsArray[I++];
	for (int i = 0; i < (int) foodArray.size(); i++) {
		CERR("Food at\t\t" << foodArray[i][0u].asInt() << "\t" << foodArray[i][1u].asInt() << ", " << foodArray[i][2u].asInt() << "\n");
		map->addEntity(
				new Food(foodArray[i][0u].asInt(), new Cell(foodArray[i][1u].asInt(),
						foodArray[i][2u].asInt())));
	}

	Json::Value &trashArray = argsArray[I++];
	for (int i = 0; i < (int) trashArray.size(); i++) {
		CERR("Trash at\t" << trashArray[i][0u].asInt() << "\t" << trashArray[i][1u].asInt() << ", " << trashArray[i][2u].asInt() << "\n");
		map->addEntity(new Trash(trashArray[i][0u].asInt(), new Cell(
				trashArray[i][1u].asInt(), trashArray[i][2u].asInt())));
	}

	Json::Value &slippersArray = argsArray[I++];
	for (int i = 0; i < (int) slippersArray.size(); i++) {
		CERR("Slippers at\t" << slippersArray[i][0u].asInt() << "\t" << slippersArray[i][1u].asInt() << ", " << slippersArray[i][2u].asInt() << "\n");
		map->addEntity(new Slippers(slippersArray[i][0u].asInt(), new Cell(
				slippersArray[i][1u].asInt(), slippersArray[i][2u].asInt())));
	}

	Json::Value &teleportArray = argsArray[I++];
	for (int i = 0; i < (int) teleportArray.size(); i++) {
		CERR("Teleport at\t" << teleportArray[i][0u].asInt() << "\t" << teleportArray[i][1u].asInt() << ", " << teleportArray[i][2u].asInt() << "\n");
		map->addEntity(
				new Teleport(teleportArray[i][0u].asInt(), new Cell(
						teleportArray[i][1u].asInt(), teleportArray[i][2u].asInt()),
						teleportArray[i][3u].asInt()));
	}
	auto teleportCells = map->getTeleportCells();
	for(auto cell : teleportCells) {
		Teleport* pair = dynamic_cast<Teleport*>(map->getEntity(cell->getTeleport()->getPairId()));
		cell->getTeleport()->setPair(pair);
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
				Cell* newCell = new Cell(row, col);

				CERR("ADD\t" << id << "\t" << row << ", " << col << "\n");
				if (type == EntityType::BEETLE) {
					Direction dir = static_cast<Direction>(singleChange[I++].asInt());
					bool wing = singleChange[I++].asBool();
					BeetleType type = static_cast<BeetleType>(singleChange[I++].asInt());
					bool sick = singleChange[I++].asBool();
					int team_id = singleChange[I++].asInt();
					map->addEntity(new Beetle(id, newCell, dir, wing, type, sick, team_id));
				} else if (type == EntityType::FOOD) {
					map->addEntity(new Food(id, newCell));
				} else if (type == EntityType::SLIPPERS) {
					map->addEntity(new Slippers(id, newCell));
				} else if (type == EntityType::TRASH) {
					map->addEntity(new Trash(id, newCell));
				} else {
					throw("unknown entity type");
				}

			} else if (changeType == "d") {
				/* delete */
				int id = singleChange[I++].asInt();
				CERR("DEL\t" << id << "\n");

				map->delEntity(id);

			} else if (changeType == "m") {
				/* move */
				int id = singleChange[I++].asInt();
				CERR("MOV\t" << id << "\n");
				Move move = static_cast<Move>(singleChange[I++].asInt());

				map->moveEntity(id, move);

			} else if (changeType == "c") {
				/* alter */
				int id = singleChange[I++].asInt();

				int x = singleChange[I++].asInt();
				int y = singleChange[I++].asInt();
				bool wing = singleChange[I++].asBool();
				bool sick = singleChange[I++].asBool();
				CERR("ALT\t" << id << "\t" << x << ", " << y << "\t" << wing << " " << sick << "\n");
				map->moveEntity(id, x, y, wing, sick);
			} else {
				/* error */
				throw("unknown change type");
			}
		}
	}
}
