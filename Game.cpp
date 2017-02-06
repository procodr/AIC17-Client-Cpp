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

long long getTimeInMilliSeconds()
{
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

Game::Game()
{
    turn = 0;
    totalTurns = 0;
    turnTimeout = 0;
    turnStartTime = -1;
    
	myID = 0;
	
	map = NULL;
}

Game::~Game()
{
	delete map;
}

void Game::setConstants(Json::Value &msg)
{
    // this->totalTurns = msg["turns"].asInt();
}

void Game::handleInitMessage(Message msg)
{
    Json::Value &argsArray = msg.getArray("args");

    Json::UInt I = 0;
    Json::UInt zero = 0;

    this->myID = argsArray[I++].asInt();

    Json::Value &sizeArray = argsArray[I++];
	Size size = {sizeArray[zero].asInt(), sizeArray[zero + 1].asInt()};
	map = new MapImp(size);

    Json::Value &roachArray = argsArray[I++];

    for (Json::UInt i = 0; i < roachArray.size(); i++)
    {
		this->insertEntity(Roach(
			roachArray[i][zero + 0].asInt(),
			{
				roachArray[i][zero + 1].asInt(),
				roachArray[i][zero + 2].asInt()
			},
			static_cast<Dir> (roachArray[i][zero + 3].asInt()),
			static_cast<Antenna> (roachArray[i][zero + 4].asInt()),
			static_cast<Type> (roachArray[i][zero + 5].asInt()),
			roachArray[i][zero + 6].asBool(),
			static_cast<Color> (roachArray[i][zero + 7].asInt())));
    }

    Json::Value &foodArray = argsArray[I++];
	for (int i = 0; i < (int)foodArray.size(); i++)
    {
		this->insertEntity(Food(
			foodArray[i][zero + 0].asInt(),
			{
				foodArray[i][zero + 1].asInt(),
				foodArray[i][zero + 2].asInt()
			}));
    }

    Json::Value &trashArray = argsArray[I++];
	for (int i = 0; i < (int)trashArray.size(); i++)
    {
		this->insertEntity(Trash(
			trashArray[i][zero + 0].asInt(),
			{
				trashArray[i][zero + 1].asInt(),
				trashArray[i][zero + 2].asInt()
			}));
    }

    Json::Value &slippersArray = argsArray[I++];
	for (int i = 0; i < (int)slippersArray.size(); i++)
    {
		this->insertEntity(Slippers(
			slippersArray[i][zero + 0].asInt(),
			{
				slippersArray[i][zero + 1].asInt(),
				slippersArray[i][zero + 2].asInt()	
			}));
    }

    Json::Value &sewerArray = argsArray[I++];
	for (int i = 0; i < (int)sewerArray.size(); i++)
    {
		this->addSewer(
		{
			{
				sewerArray[i][zero + 0].asInt(),
				sewerArray[i][zero + 1].asInt()
			},
			{
				sewerArray[i][zero + 2].asInt(),
				sewerArray[i][zero + 3].asInt()
			}
		});
    }

    Json::Value &constants = argsArray[I++];
    this->setConstants(constants);
}

void Game::handleTurnMessage(Message msg)
{
    turnStartTime = getTimeInMilliSeconds();

    Json::Value &argsArray = msg.getArray("args");
    
	Json::UInt I = 0;
    Json::UInt zero = 0;
    
	turn = argsArray[I++].asInt();

    Json::Value &scores = argsArray[I++];
    score = std::make_pair(scores[zero + 0].asInt(), scores[zero + 1].asInt());

	Json::Value &changesArray = argsArray[I++];
	for (int i = 0; i < (int)changesArray.size(); i++)
    {
		// Json::UInt j = 0;
		Json::Value &change = changesArray[i];
		
		if (change["type"] == "a")
		{
			// Json::Value &changeArgs = change["args"];
			/* TODO */
		}
		else if (change["type"] == "d")
		{
			/* TODO */
		}
		else if (change["type"] == "m")
		{
			/* TODO */
		}
		else if (change["type"] == "c")
		{
			/* TODO */
		}
		else
		{
			throw("unknown change type");
		}
	}
}

long long Game::getTurnTimePassed()
{
    return getTimeInMilliSeconds() - turnStartTime;
}

long long Game::getTurnRemainingTime()
{
	return turnTimeout - getTurnTimePassed();
}

int Game::getMyId()
{
	return myID;
}

MapImp &Game::getMap()
{
	return *map;
}

Entity &Game::getEntity(int id)
{
	return entities[id];
}

std::vector<Sewer> &Game::getSewers()
{
	return this->sewers;
}

int Game::getTurnNumber()
{
	return this->turn;
}

long long Game::getTotalTurnTime()
{
	return this->turnTimeout;
}

void Game::changeStrategy(Antenna t, int i, int j, int k, Move s)
{
	GameEvent* ev = new GameEvent(Constants::TYPE_CHANGE_STRATEGY);
	ev->addArg(static_cast<int>(t));
	ev->addArg(i);
	ev->addArg(j);
	ev->addArg(k);
	ev->addArg(static_cast<int>(s));
	eventHandler->addEvent(ev);
}

void Game::deterministicMove(const Roach &roach, Move s)
{
	GameEvent* ev = new GameEvent(Constants::TYPE_DETERMINISTIC_MOVE);
	ev->addArg(roach.getId());
	ev->addArg(static_cast<int>(s));
	eventHandler->addEvent(ev);
}

void Game::antennaChange(const Roach& roach)
{
	GameEvent* ev = new GameEvent(Constants::TYPE_ANTENNA_CHANGE);
	ev->addArg(roach.getId());
	eventHandler->addEvent(ev);
}

void Game::insertEntity(Entity entity)
{
	int id = entity.getId();
	entities.insert({id, entity});
	map->addEntity(entities[id]);
}

void Game::deleteEntity(int id)
{
	Cell pos = entities[id].getPos();
	map->delEntity(pos.x, pos.y);
	entities.erase(id);
}

void Game::addSewer(Sewer sewer)
{
	sewers.push_back(sewer);
	map->addSewer(sewer);
}
