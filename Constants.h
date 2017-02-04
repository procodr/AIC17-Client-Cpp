/*
 * Constants.h
 *
 *  Created on: Feb 16, 2015
 *      Author: rmin
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

class Constants {
public:
	static const std::string MESSAGE_KEY_TYPE;
	static const std::string MESSAGE_KEY_NAME;
	static const std::string MESSAGE_KEY_ARGS;
	static const std::string MESSAGE_KEY_TURN;
	static const std::string MESSAGE_KEY_INIT;
	static const std::string MESSAGE_KEY_TOKEN;
	static const std::string MESSAGE_KEY_EVENT;
	static const std::string MESSAGE_KEY_SHUTDOWN;
	static const std::string MESSAGE_KEY_WRONG_TOKEN;

	static const std::string TYPE_MOVE;

	static const int ARGS_NUMBER_MOVE;
};

#endif /* CONSTANTS_H_ */
