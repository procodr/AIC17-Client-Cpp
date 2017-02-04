#ifndef _EVENT_H
#define _EVENT_H

#include <vector>
#include <string>
#include "Constants.h"

/**
 * Event class.
 */

class Event
{
public:
	Event(std::string type);

    std::string getType();
    const std::vector<int>& getArgs();

protected:
	/** The type of the Event **/
    std::string type;			
    /** Arguments of the Event **/
    std::vector<int> args;
};

#endif
