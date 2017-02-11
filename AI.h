#ifndef AI_H
#define AI_H

#include "Beetle.h"
#include "Map.h"
#include "World.h"
#include "Types.h"
#include "Slippers.h"
#include "Trash.h"
#include "Food.h"

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

#endif /* AI_H */
