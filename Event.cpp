#include "Event.h"

Event::Event(std::string type)
{
	this->type = type;
}

std::string Event::getType()
{
	return type;
}

const std::vector<int>& Event::getArgs()
{
    return args;
}
