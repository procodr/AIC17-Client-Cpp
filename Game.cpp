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

void Game::setConstants(Json::Value &msg) {
    this->turnTimeout = msg[0u].asInt();
    this->foodProb = msg[1u].asDouble();
    this->trashProb = msg[2u].asDouble();
    this->netProb = msg[3u].asDouble();
    this->netValidTime = msg[4u].asInt();
    this->colorCost = msg[5u].asInt();
    this->sickCost = msg[6u].asInt();
    this->updateCost = msg[7u].asInt();
    this->detMoveCost = msg[8u].asInt();
    this->killQueenScore = msg[9u].asInt();
    this->killBothQueenScore = msg[10u].asInt();
    this->killFishScore = msg[11u].asInt();
    this->queenCollisionScore = msg[12u].asInt();
    this->fishFoodScore = msg[13u].asInt();
    this->queenFoodScore = msg[14u].asInt();
    this->sickLifeTime = msg[15u].asInt();
    this->powerRatio = msg[16u].asDouble();
    this->endRatio = msg[17u].asDouble();
    this->disobeyNum = msg[18u].asInt();
    this->foodValidTime = msg[19u].asInt();
    this->trashValidTime = msg[20u].asInt();
}

void Game::handleInitMessage(Message msg) {
    Json::Value &argsArray = msg.getArray("args");

    Json::UInt I = 0;

    this->myID = argsArray[I++].asInt();

    Json::Value &sizeArray = argsArray[I++];
    Size size = {sizeArray[0u].asInt(), sizeArray[1u].asInt()};
    map = new MapImp(size);

    Json::Value &roachArray = argsArray[I++];

    for (Json::UInt i = 0; i < roachArray.size(); i++) {
        this->insertEntity(new RoachImp(
                roachArray[i][0u].asInt(),
                {
                        roachArray[i][1u].asInt(),
                        roachArray[i][2u].asInt()
                },
                static_cast<Dir> (roachArray[i][3u].asInt()),
                static_cast<Antenna> (roachArray[i][4u].asInt()),
                static_cast<Type> (roachArray[i][5u].asInt()),
                roachArray[i][6u].asBool(),
                static_cast<Color> (roachArray[i][7u].asInt())));
    }

    Json::Value &foodArray = argsArray[I++];
    for (int i = 0; i < (int) foodArray.size(); i++) {
        this->insertEntity(new Food(
                foodArray[i][0u].asInt(),
                {
                        foodArray[i][1u].asInt(),
                        foodArray[i][2u].asInt()
                }));
    }

    Json::Value &trashArray = argsArray[I++];
    for (int i = 0; i < (int) trashArray.size(); i++) {
        this->insertEntity(new Trash(
                trashArray[i][0u].asInt(),
                {
                        trashArray[i][1u].asInt(),
                        trashArray[i][2u].asInt()
                }));
    }

    Json::Value &slippersArray = argsArray[I++];
    for (int i = 0; i < (int) slippersArray.size(); i++) {
        this->insertEntity(new Slippers(
                slippersArray[i][0u].asInt(),
                {
                        slippersArray[i][1u].asInt(),
                        slippersArray[i][2u].asInt()
                }));
    }

    Json::Value &sewerArray = argsArray[I++];
    for (int i = 0; i < (int) sewerArray.size(); i++) {
        this->insertEntity(new Sewer(
                sewerArray[i][0u].asInt(),
                {
                        sewerArray[i][1u].asInt(),
                        sewerArray[i][2u].asInt()
                },
                sewerArray[i][3u].asInt()));
    }

    Json::Value &constants = argsArray[I++];
    this->setConstants(constants);
}

void Game::handleTurnMessage(Message msg) {
	turnStartTime = getTimeInMilliSeconds();

    Json::Value &argsArray = msg.getArray("args");

    Json::UInt I = 0;

    turn = argsArray[I++].asInt();

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
                Cell pos = {singleChange[I++].asInt(), singleChange[I++].asInt()};
                if (type == EntityType::ROACH) {
                    Dir dir = static_cast<Dir>(singleChange[I++].asInt());
                    Antenna antenna = static_cast<Antenna>(singleChange[I++].asInt());
                    Type type = static_cast<Type>(singleChange[I++].asInt());
                    bool sick = singleChange[I++].asBool();
                    Color color = static_cast<Color>(singleChange[I++].asInt());
                    this->insertEntity(new RoachImp(
                            id, pos, dir, antenna, type, sick, color
                    ));
                } else if (type == EntityType::FOOD) {
                    this->insertEntity(new Food(id, pos));
                } else if (type == EntityType::SLIPPERS) {
                    this->insertEntity(new Slippers(id, pos));
                } else if (type == EntityType::TRASH) {
                    this->insertEntity(new Trash(id, pos));
                } else {
                    throw ("unknown entity type");
                }

            } else if (changeType == "d") {
                /* delete */
            	int id = singleChange[0u].asInt();
                this->deleteEntity(id);

            } else if (changeType == "m") {
                /* move */
                int id = singleChange[0u].asInt();
                RoachImp* roach = dynamic_cast<RoachImp *>(this->getEntity(id));

                Move move = static_cast<Move>(singleChange[1u].asInt());

                int x = roach->getPos().row;
                int y = roach->getPos().col;
                int w = map->getSize().w;
                int h = map->getSize().h;

                if (move == Move::FORWARD)
                    map->delEntity(x, y, id);

                roach->doMove(move, w, h);

                if (move == Move::FORWARD)
                    map->addEntity(roach);

            } else if (changeType == "c") {
                /* alter */
                int id = singleChange[0u].asInt();
                Antenna antenna = static_cast<Antenna>(singleChange[1u].asInt());
                bool sick = singleChange[2u].asBool();
                dynamic_cast<RoachImp *>(this->getEntity(id))->alter(sick, antenna);

            } else {
                /* error */
                throw ("unknown change type");
            }
        }
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

MapImp &Game::getMap() {
    return *map;
}

Entity* Game::getEntity(int id) {
    return entities[id];
}

int Game::getTurnNumber() {
    return this->turn;
}

long long Game::getTotalTurnTime() {
    return this->turnTimeout;
}

void Game::changeStrategy(Antenna t, int i, int j, int k, Move s) {
    GameEvent *ev = new GameEvent(Constants::TYPE_CHANGE_STRATEGY);
    ev->addArg(static_cast<int>(t));
    ev->addArg(i);
    ev->addArg(j);
    ev->addArg(k);
    ev->addArg(static_cast<int>(s));
    eventHandler->addEvent(ev);
}

void Game::deterministicMove(const Roach &roach, Move s) {
    GameEvent *ev = new GameEvent(Constants::TYPE_DETERMINISTIC_MOVE);
    ev->addArg(roach.getId());
    ev->addArg(static_cast<int>(s));
    eventHandler->addEvent(ev);
}

void Game::antennaChange(const Roach &roach) {
    GameEvent *ev = new GameEvent(Constants::TYPE_ANTENNA_CHANGE);
    ev->addArg(roach.getId());
    eventHandler->addEvent(ev);
}

void Game::insertEntity(Entity* entity) {
    int id = entity->getId();

    std::cerr << "ADD : " << id << '\n';

    entities.insert({id, entity});

    Sewer *sewer = dynamic_cast<Sewer *> (entity);
    Slippers *slippers = dynamic_cast<Slippers *> (entity);

    if (sewer) {
    	Sewer *otherSewer = dynamic_cast<Sewer *> (this->getEntity(sewer->getDestId()));
    	if (otherSewer) {
    		map->addSewer(*sewer, otherSewer->getPos());
    		map->addSewer(*otherSewer, sewer->getPos());
    	}
    } else if (slippers) {
        map->addShadow(slippers->getPos().row, slippers->getPos().col);
    } else {
        map->addEntity(entity);
    }
}

void Game::deleteEntity(int id) {

	std::cerr << "DEL : " << id << '\n';

	if (entities[id] == NULL) {
		std::cerr << 1/0 << std::endl;
	}
    Cell pos = entities[id]->getPos();
    map->delEntity(pos.row, pos.col, id);
    entities.erase(id);
}

int Game::getTurnTimeout() const {
    return turnTimeout;
}

double Game::getFoodProb() const {
    return foodProb;
}

double Game::getTrashProb() const {
    return trashProb;
}

double Game::getNetProb() const {
    return netProb;
}

int Game::getNetValidTime() const {
    return netValidTime;
}

int Game::getColorCost() const {
    return colorCost;
}

int Game::getSickCost() const {
    return sickCost;
}

int Game::getUpdateCost() const {
    return updateCost;
}

int Game::getDetMoveCost() const {
    return detMoveCost;
}

int Game::getKillQueenScore() const {
    return killQueenScore;
}

int Game::getKillBothQueenScore() const {
    return killBothQueenScore;
}

int Game::getKillFishScore() const {
    return killFishScore;
}

int Game::getQueenCollisionScore() const {
    return queenCollisionScore;
}

int Game::getFishFoodScore() const {
    return fishFoodScore;
}

int Game::getQueenFoodScore() const {
    return queenFoodScore;
}

int Game::getSickLifeTime() const {
    return sickLifeTime;
}

double Game::getPowerRatio() const {
    return powerRatio;
}

double Game::getEndRatio() const {
    return endRatio;
}

int Game::getDisobeyNum() const {
    return disobeyNum;
}

int Game::getFoodValidTime() const {
    return foodValidTime;
}

int Game::getTrashValidTime() const {
    return trashValidTime;
}
