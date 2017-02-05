#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include "Event.h"

#include <string>

class GameEvent : public Event
{
  public:
    GameEvent(Event event);
    GameEvent(std::string type);
    void setArg(int value, int index);
    void addArg(int value);
    virtual ~GameEvent();
};

#endif /* GAMEEVENT_H */
