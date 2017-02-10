#ifndef AIC_TYPES
#define AIC_TYPES

#include <unordered_map>

class Entity;

typedef std::pair<int, Entity*> PIE;

typedef std::unordered_map<int, Entity *> EntityDict;

enum class Antenna
{
    SINGLE = 0,
    DOUBLE
};

enum class Type
{
    WINGED = 0,
    NORMAL
};

enum class Color
{
    BRIGHT = 0,
    BROWN
};

enum class Dir
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
	ROACH = 0,
	FOOD,
	TRASH, 
	SLIPPERS,
    SEWER
};

struct Size
{
    int w, h;
};

class Cell
{
public:
    int row, col;
    Cell(int row, int col) : row(row), col(col) {}
};

#endif /* AIC_TYPES */
