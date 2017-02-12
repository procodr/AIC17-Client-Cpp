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
#include "Queue.h"

EventHandler::EventHandler(Network* network) {
    this->network = network;
    this->alive = true;
    this->thread = new std::thread(&EventHandler::handling, this);
}

EventHandler::~EventHandler() {
    this->alive = false;
    this->thread->detach();
    delete this->thread;
}

void EventHandler::handling() {
    while (this->alive) handleEvent(events.pop());
}

void EventHandler::addEvent(GameEvent* event) { events.push(event); }

void EventHandler::handleEvent(GameEvent* eve) {
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
