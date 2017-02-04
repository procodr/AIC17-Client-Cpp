/*
 * Parser.h
 *
 *  Created on: Feb 15, 2015
 *      Author: rmin
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "Message.h"
#include <vector>
#include "GameEvent.h"

class Parser {
public:
	Parser();
	virtual ~Parser();
	void generateEvent(Message &msg, GameEvent &event);
};

#endif /* PARSER_H_ */
