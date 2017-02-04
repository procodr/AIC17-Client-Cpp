/*
 * EventHandler.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: rmin
 */

#include "EventHandler.h"
#include "Parser.h"
#include <chrono>
#include <future>

EventHandler::EventHandler(Network *network)
{
	this->network = network;
	isThreadCall = false;
	thr = NULL;
}

bool EventHandler::getIsThreadCall()
{
	return isThreadCall;
}

std::thread * EventHandler::getThr()
{
	return thr;
}

EventHandler::~EventHandler()
{
}

void EventHandler::handling()
{
	while (events.getSize() != 0)
	{
		handleEvent(events.pop());
	}
	isThreadCall = false;
}

void EventHandler::addEvent(GameEvent* event) {
	events.push(event);
	if (!isThreadCall) {
		isThreadCall = true;
		thr = new std::thread(&EventHandler::handling,this);
	}
}

void EventHandler::handleEvent(GameEvent *eve)
{
	Message result, event;
	result.addNode(Constants::MESSAGE_KEY_NAME, Constants::MESSAGE_KEY_EVENT);
	parser.generateEvent(event, *eve);
	std::vector<Message> eventsJson;
	eventsJson.push_back(event);
	result.addArray(Constants::MESSAGE_KEY_ARGS, eventsJson);
	network->sendMessage(result);
	delete eve;
}

EventHandler* eventHandler;
