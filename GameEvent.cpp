/*
 * GameEvent.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#include "GameEvent.h"

GameEvent::GameEvent(Event event) : Event(event) {}

GameEvent::GameEvent(std::string type) : Event(type)
{
    this->type = type;
    if (type != Constants::TYPE_CHANGE_STRATEGY
	 && type != Constants::TYPE_DETERMINISTIC_MOVE
	 && type != Constants::TYPE_COLOR_CHANGE)
	{
		throw "UNKNOWN EVENT TYPE\n";
	}
}

void GameEvent::addArg(int value)
{
    args.push_back(value);
}

void GameEvent::setArg(int value, int index)
{
    if (index < (int)args.size() && index >= 0)
		args[index] = value;
}

GameEvent::~GameEvent() {}
