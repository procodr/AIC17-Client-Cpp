/*
 * Constants.h
 *
 *  Created on: Feb 16, 2015
 *      Author: rmin
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

class Constants
{
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

    static const std::string Constants::TYPE_CHANGE_STRATEGY;
    static const std::string Constants::TYPE_DETERMINISTIC_MOVE;
    static const std::string Constants::TYPE_COLOR_CHANGE;

    static const int Constants::ARGS_NUMBER_CHANGE_STRATEGY;
    static const int Constants::ARGS_NUMBER_DETERMINISTIC_MOVE;
    static const int Constants::ARGS_NUMBER_COLOR_CHANGE;
};

#endif /* CONSTANTS_H_ */
