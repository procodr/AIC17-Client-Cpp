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

    static const std::string TYPE_CHANGE_STRATEGY;
    static const std::string TYPE_DETERMINISTIC_MOVE;
    static const std::string TYPE_COLOR_CHANGE;

    static const int ARGS_NUMBER_CHANGE_STRATEGY;
    static const int ARGS_NUMBER_DETERMINISTIC_MOVE;
    static const int ARGS_NUMBER_COLOR_CHANGE;
};

#endif /* CONSTANTS_H */
