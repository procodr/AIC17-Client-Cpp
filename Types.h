#ifndef AIC_TYPES
#define AIC_TYPES

#include <unordered_map>

class Entity;

namespace aic
{
typedef std::unordered_map<int, Entity> EntityDict;

enum class Antenna
{
    SINGLE,
    DOUBLE
};

enum class Type
{
    WINGED,
    NORMAL
};

enum class Color
{
    BRIGHT,
    BROWN
};

enum class Dir
{
    LEFT,
    UP,
    RIGHT,
    DOWN
};

enum class Move
{
    RIGHT,
    FORWARD,
    LEFT
};

struct Size
{
    int w, h;
};

struct Cell
{
    int x, y;
};

/* end of namespace aic */
}

#endif /* AIC_TYPES */
