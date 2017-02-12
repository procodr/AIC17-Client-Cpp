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
#include "Queue.h"

class EventHandler {
	Parser parser;
	Queue<GameEvent*> events;
	Network *network;
    bool alive;
    std::thread *thread;
public:
	EventHandler(Network *network);
	virtual ~EventHandler();
	void handleEvent(GameEvent* eve);
	void handling();
	void addEvent(GameEvent *event);
};

extern EventHandler* eventHandler;

#endif /* EVENTHANDLER_H_ */
