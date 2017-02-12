#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include "jsoncpp-src-0.5.0/include/json/json.h"

class Constants {
public:
	static const std::string MESSAGE_KEY_TYPE;
	static const std::string MESSAGE_KEY_NAME;
	static const std::string MESSAGE_KEY_ARGS;
	static const std::string MESSAGE_KEY_TURN;
	static const std::string MESSAGE_KEY_INIT;
	static const std::string MESSAGE_KEY_TOKEN;
	static const std::string MESSAGE_KEY_EVENT;
	static const std::string MESSAGE_KEY_SHUTDOWN;
	static const std::string MESSAGE_KEY_WRONG_TOKEN;

	static const std::string TYPE_CHANGE_STRATEGY;
	static const std::string TYPE_DETERMINISTIC_MOVE;
	static const std::string TYPE_ANTENNA_CHANGE;

	static const int ARGS_NUMBER_CHANGE_STRATEGY;
	static const int ARGS_NUMBER_DETERMINISTIC_MOVE;
	static const int ARGS_NUMBER_ANTENNA_CHANGE;

	double foodProb;
	double trashProb;
	double slipperProb;
	int typeChangeCost;
	int sickCost;
	int updateCost;
	int detMoveCost;
	int killWingedScore;
	int killBothWingedScore;
	int killBeetleScore;
	int wingedCollisionScore;
	int beetleFoodScore;
	int wingedBeetleFoodScore;
	int sickLifeTime;
	double powerRatio;
	double endRatio;
	int disobeyConstant;
	int foodValidTime;
	int trashValidTime;
	int slipperValidTime;

    void setConstants(Json::Value &msg);

	/**
	 * Probability of a food showing up in any of the tiles without content(Roach or Food)
	 *
	 * @return Food probability
	 */
	double getFoodProb() const;

	/**
	 * Probability of a trash showing up in any of the tiles without content(Roach or Food)
	 *
	 * @return Trash probability
	 */
	double getTrashProb() const;

	/**
	 * Probability of a net showing up in any of the tiles without a net
	 *
	 * @return Net probability
	 */
	double getSlipperProb() const;

	/**
	 * Cost of changing the antenna of a roach
	 *
	 * @return Antenna cost
	 */
	int getTypeChangeCost() const;

	/**
	 * Sick roachs give points to the opposing team of all their 8 neighbours
	 *
	 * @return Given points for each neighbour
	 */
	int getSickCost() const;

	/**
	 *
	 * @return Cost of changing strategy
	 */
	int getUpdateCost() const;

	/**
	 *
	 * @return Cost of a deterministic move
	 */
	int getDetMoveCost() const;

	/**
	 *
	 * @return Points achieved when a normal roach kills a queen
	 */
	int getKillWingedScore() const;

	/**
	 *
	 * @return Points achieved when two queens kill each other
	 */
	int getKillBothWingedScore() const;

	/**
	 *
	 * @return Points achieved from killing a normal roach
	 */
	int getKillBeetleScore() const;

	/**
	 *
	 * @return Points achieved when a normal roach consumes food
	 */
	int getBeetleFoodScore() const;

	/**
	 *
	 * @return Points achieved when a queen roach consumes food
	 */
	int getWingedBeetleFoodScore() const;

	/**
	 *
	 * @return Beetle's lifespan since getting sick
	 */
	int getSickLifeTime() const;

	/**
	 *
	 * @return Amount of power that a roach achieves each turn
	 */
	double getPowerRatio() const;

	/**
	 * If the map is "end ratio" percent full, the game ends
	 *
	 * @return End ratio
	 */
	double getEndRatio() const;

	/**
	 *
	 * @return Minimum roach population required for a roach to disobey
	 */
	int getDisobeyConstant() const;

	/**
	 *
	 * @return Amount of turns a food stays on the map
	 */
	int getFoodValidTime() const;

	/**
	 *
	 * @return Amount of turns a trash stays on the map
	 */
	int getTrashValidTime() const;

	/**
	 *
	 * @return Amount of turns a slipper stays on the map
	 */
	int getSlipperValidTime() const;
};

#endif /* CONSTANTS_H */
