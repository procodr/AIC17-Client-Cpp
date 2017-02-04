/*
 * EventHandler.h
 *
 *  Created on: Feb 16, 2015
 *      Author: rmin
 */

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "GameEvent.h"
#include <thread>
#include "Network.h"
#include "Parser.h"
#include "Message.h"
#include <vector>
#include "Queue.cpp"

class EventHandler {
	Parser parser;
	bool isThreadCall;
	std::thread* thr;
	Queue<GameEvent*> events;
	Network *network;
public:
	EventHandler(Network *network);
	virtual ~EventHandler();
	void handleEvent(GameEvent* eve);
	void handling();
	bool getIsThreadCall();
	std::thread* getThr();
	void addEvent(GameEvent *event);
};

extern EventHandler* eventHandler;

#endif /* EVENTHANDLER_H_ */
