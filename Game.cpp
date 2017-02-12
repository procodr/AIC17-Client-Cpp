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
    this->turnTimeout = msg["turnTimeout"].asInt();
    this->foodProb = msg["foodProb"].asDouble();
    this->trashProb = msg["trashProb"].asDouble();
    this->netProb = msg["netProb"].asDouble();
    this->netValidTime = msg["netValidTime"].asInt();
    this->colorCost = msg["colorCost"].asInt();
    this->sickCost = msg["sickCost"].asInt();
    this->updateCost = msg["updateCost"].asInt();
    this->detMoveCost = msg["detMoveCost"].asInt();
    this->killQueenScore = msg["killQueenScore"].asInt();
    this->killBothQueenScore = msg["killBothQueenScore"].asInt();
    this->killFishScore = msg["killFishScore"].asInt();
    this->queenCollisionScore = msg["queenCollisionScore"].asInt();
    this->fishFoodScore = msg["fishFoodScore"].asInt();
    this->queenFoodScore = msg["queenFoodScore"].asInt();
    this->sickLifeTime = msg["sickLifeTime"].asInt();
    this->powerRatio = msg["powerRatio"].asDouble();
    this->endRatio = msg["endRation"].asDouble();
    this->disobeyNum = msg["disobeyNum"].asInt();
    this->foodValidTime = msg["foodValidTime"].asInt();
    this->trashValidTime = msg["trashValidTime"].asInt();
}

void Game::handleInitMessage(Message msg) {
    Json::Value &argsArray = msg.getArray("args");

    Json::UInt I = 0;
    Json::UInt zero = 0;

    this->myID = argsArray[I++].asInt();

    Json::Value &sizeArray = argsArray[I++];
    Size size = {sizeArray[zero].asInt(), sizeArray[zero + 1].asInt()};
    map = new MapImp(size);

    Json::Value &roachArray = argsArray[I++];

    for (Json::UInt i = 0; i < roachArray.size(); i++) {
        this->insertEntity(RoachImp(
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
    for (int i = 0; i < (int) foodArray.size(); i++) {
        this->insertEntity(Food(
                foodArray[i][zero + 0].asInt(),
                {
                        foodArray[i][zero + 1].asInt(),
                        foodArray[i][zero + 2].asInt()
                }));
    }

    Json::Value &trashArray = argsArray[I++];
    for (int i = 0; i < (int) trashArray.size(); i++) {
        this->insertEntity(Trash(
                trashArray[i][zero + 0].asInt(),
                {
                        trashArray[i][zero + 1].asInt(),
                        trashArray[i][zero + 2].asInt()
                }));
    }

    Json::Value &slippersArray = argsArray[I++];
    for (int i = 0; i < (int) slippersArray.size(); i++) {
        this->insertEntity(Slippers(
                slippersArray[i][zero + 0].asInt(),
                {
                        slippersArray[i][zero + 1].asInt(),
                        slippersArray[i][zero + 2].asInt()
                }));
    }

    Json::Value &sewerArray = argsArray[I++];
    for (int i = 0; i < (int) sewerArray.size(); i++) {
        this->insertEntity(Sewer(
                sewerArray[i][zero + 0].asInt(),
                {
                        sewerArray[i][zero + 1].asInt(),
                        sewerArray[i][zero + 2].asInt()
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
    Json::UInt zero = 0;

    turn = argsArray[I++].asInt();

    Json::Value &scores = argsArray[I++];
    score = std::make_pair(scores[zero + 0].asInt(), scores[zero + 1].asInt());

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
                Cell pos = {singleChange[I++].asInt(), singleChange[I++].asInt()};
                std::string type = singleChange[I++].asString();
                if (type == "roach") {
                    Dir dir = static_cast<Dir>(singleChange[I++].asInt());
                    Antenna antenna = static_cast<Antenna>(singleChange[I++].asInt());
                    Type type = static_cast<Type>(singleChange[I++].asInt());
                    bool sick = singleChange[I++].asBool();
                    Color color = static_cast<Color>(singleChange[I++].asInt());
                    this->insertEntity(RoachImp(
                            id, pos, dir, antenna, type, sick, color
                    ));
                } else if (type == "food") {
                    this->insertEntity(Food(id, pos));
                } else if (type == "slippers") {
                    this->insertEntity(Slippers(id, pos));
                } else if (type == "trash") {
                    this->insertEntity(Trash(id, pos));
                } else {
                    throw ("unknown entity type");
                }

            } else if (changeType == "d") {
                /* delete */
                this->deleteEntity(singleChange[j].asInt());

            } else if (changeType == "m") {
                /* move */
                int id = singleChange[0u].asInt();
                Move move = static_cast<Move>(singleChange[1u].asInt());
                int w = map->getSize().w;
                int h = map->getSize().h;
                dynamic_cast<RoachImp *>(&this->getEntity(id))->doMove(move, w, h);

            } else if (changeType == "c") {
                /* alter */
                int id = singleChange[0u].asInt();
                Antenna antenna = static_cast<Antenna>(singleChange[1u].asInt());
                bool sick = singleChange[2u].asBool();
                dynamic_cast<RoachImp *>(&this->getEntity(id))->alter(sick, antenna);

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

Entity &Game::getEntity(int id) {
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

void Game::insertEntity(Entity entity) {
    int id = entity.getId();
    entities.insert({id, entity});

    Sewer *sewer = dynamic_cast<Sewer *> (&entity);
    Slippers *slippers = dynamic_cast<Slippers *> (&entity);

    if (sewer) {
        map->addSewer(*sewer, this->getEntity(sewer->getDestId()).getPos());
    } else if (slippers) {
        map->addShadow(slippers->getPos().x, slippers->getPos().y);
    } else {
        map->addEntity(entities[id]);
    }
}

void Game::deleteEntity(int id) {
    Cell pos = entities[id].getPos();
    map->delEntity(pos.x, pos.y);
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

