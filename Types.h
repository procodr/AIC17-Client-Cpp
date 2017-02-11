#ifndef AIC_TYPES
#define AIC_TYPES

#include <iostream>

extern int globalTurn;

class Entity;

typedef std::pair<int, Entity*> PIE;

//enum class Antenna
//{
//    SINGLE = 0,
//    DOUBLE
//};

enum class BeetleType
{
    LOW = 0,
    HGIGH
};

//enum class BeetleColor
//{
//    BRIGHT = 0,
//    BROWN
//};

enum class Direction
{
    RIGHT = 0,
    UP,
    LEFT,
    DOWN
};

enum class Move
{
    RIGHT = 0,
    FORWARD,
    LEFT
};

enum class EntityType
{
	BEETLE = 0,
	FOOD,
	TRASH, 
	SLIPPERS,
    TELEPORT
};

enum class CellState {
	ALLY = 0,
	ENEMY,
	BLANK
};

struct Size
{
    int width, height;
};


#endif /* AIC_TYPES */
