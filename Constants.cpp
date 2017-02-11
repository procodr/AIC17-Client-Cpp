/*
 * Constants.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: rmin
 */

#include "Constants.h"
#include "Food.h"
#include "Slippers.h"
#include "Trash.h"

const std::string Constants::MESSAGE_KEY_TYPE = "type";
const std::string Constants::MESSAGE_KEY_NAME = "name";
const std::string Constants::MESSAGE_KEY_ARGS = "args";
const std::string Constants::MESSAGE_KEY_TURN = "turn";
const std::string Constants::MESSAGE_KEY_INIT = "init";
const std::string Constants::MESSAGE_KEY_TOKEN = "token";
const std::string Constants::MESSAGE_KEY_EVENT = "event";
const std::string Constants::MESSAGE_KEY_WRONG_TOKEN = "wrong token";
const std::string Constants::MESSAGE_KEY_SHUTDOWN = "shutdown";

const std::string Constants::TYPE_CHANGE_STRATEGY = "s";
const std::string Constants::TYPE_DETERMINISTIC_MOVE = "m";
const std::string Constants::TYPE_ANTENNA_CHANGE = "c";

const int Constants::ARGS_NUMBER_CHANGE_STRATEGY = 5;
const int Constants::ARGS_NUMBER_DETERMINISTIC_MOVE = 2;
const int Constants::ARGS_NUMBER_ANTENNA_CHANGE = 1;

void Constants::setConstants(Json::Value &msg) {
	this->foodProb = msg[1u].asDouble();
	this->trashProb = msg[2u].asDouble();
	this->slipperProb = msg[3u].asDouble();
	this->slipperValidTime = msg[4u].asInt();
	this->typeChangeCost = msg[5u].asInt();
	this->sickCost = msg[6u].asInt();
	this->updateCost = msg[7u].asInt();
	this->detMoveCost = msg[8u].asInt();
	this->killWingedScore = msg[9u].asInt();
	this->killBothWingedScore = msg[10u].asInt();
	this->killBeetleScore = msg[11u].asInt();
	this->wingedCollisionScore = msg[12u].asInt();
	this->beetleFoodScore = msg[13u].asInt();
	this->wingedBeetleFoodScore = msg[14u].asInt();
	this->sickLifeTime = msg[15u].asInt();
	this->powerRatio = msg[16u].asDouble();
	this->endRatio = msg[17u].asDouble();
	this->disobeyConstant = msg[18u].asInt();
	this->foodValidTime = msg[19u].asInt();
	this->trashValidTime = msg[20u].asInt();

	Food::validTime = this->foodValidTime;
	Slippers::validTime = this->slipperValidTime;
	Trash::validTime = this->trashValidTime;
}


double Constants::getFoodProb() const {
	return foodProb;
}

double Constants::getTrashProb() const {
	return trashProb;
}

double Constants::getSlipperProb() const {
	return slipperProb;
}

int Constants::getTypeChangeCost() const {
	return typeChangeCost;
}

int Constants::getSickCost() const {
	return sickCost;
}

int Constants::getUpdateCost() const {
	return updateCost;
}

int Constants::getDetMoveCost() const {
	return detMoveCost;
}

int Constants::getKillWingedScore() const {
	return killWingedScore;
}

int Constants::getKillBothWingedScore() const {
	return killBothWingedScore;
}

int Constants::getKillBeetleScore() const {
	return killBeetleScore;
}

int Constants::getBeetleFoodScore() const {
	return beetleFoodScore;
}

int Constants::getWingedBeetleFoodScore() const {
	return wingedBeetleFoodScore;
}

int Constants::getSickLifeTime() const {
	return sickLifeTime;
}

double Constants::getPowerRatio() const {
	return powerRatio;
}

double Constants::getEndRatio() const {
	return endRatio;
}

int Constants::getDisobeyConstant() const {
	return disobeyConstant;
}

int Constants::getFoodValidTime() const {
	return foodValidTime;
}

int Constants::getTrashValidTime() const {
	return trashValidTime;
}

int Constants::getSlipperValidTime() const {
	return trashValidTime;
}
