#include "GameEvent.h"
#include "Constants.h"

GameEvent::GameEvent(Event event) : Event(event) {}

GameEvent::GameEvent(std::string type) : Event(type)
{
    if (type != Constants::TYPE_CHANGE_STRATEGY
	 && type != Constants::TYPE_DETERMINISTIC_MOVE
	 && type != Constants::TYPE_ANTENNA_CHANGE)
	{
		throw "Unknown event type\n";
	}
}

GameEvent::~GameEvent() {}

void GameEvent::addArg(int value)
{
    args.push_back(value);
}

void GameEvent::setArg(int value, int index)
{
    if (0 <= index && index < (int)args.size())
		args[index] = value;
}