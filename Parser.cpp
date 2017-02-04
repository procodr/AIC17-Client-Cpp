/*
 * Parser.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: rmin
 */

#include "Parser.h"

Parser::Parser() {
	// TODO Auto-generated constructor stub

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

void Parser::generateEvent(Message &msg, GameEvent &event) {
	msg.addNode(Constants::MESSAGE_KEY_TYPE, event.getType());
	std::vector<int> args;
	for (int i = 0; i < (int) event.getArgs().size(); i++) {
		args.push_back(event.getArgs()[i]);
	}
	msg.addArray(Constants::MESSAGE_KEY_ARGS, args);
}
