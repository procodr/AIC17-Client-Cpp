#ifndef _AI_H
#define _AI_H

#include "Node.h"
#include "World.h"

/**
 * AI class.
 * You should fill body of the method {@link #doTurn}.
 * Do not change name or modifiers of the methods or fields
 * and do not add constructor for this class.
 * You can add as many methods or fields as you want!
 * Use world parameter to access and modify game's world!
 * See World interface for more details.
 */
class AI
{
public:
	void doTurn(World *world);
};

#endif // _AI_H
