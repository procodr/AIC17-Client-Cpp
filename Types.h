#ifndef AIC_TYPES
#define AIC_TYPES

namespace aic
{

enum class Antenna
{
    ONE_ANTENNA,
    TWO_ANTENNA
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

struct Size
{
    int w, h;
};

struct Cell
{
    int x, y;
};

struct Sewer
{
    Cell a, b;
};

/* end of namespace aic */
}

#endif