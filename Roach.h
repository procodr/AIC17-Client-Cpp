#ifndef ROACH_H
#define ROACH_H

#include <utility>
#include "Types.h"

using namespace aic;

class Roach {
public:
	Roach(int id, Cell pos, Dir dir, Team team, Type type, bool sick, Color color)

	int getId();
	Cell getPos();
	Color getColor();
	Antenna getAntenna();
	Type getType();
	Dir getDirection();
	bool isSick();
	bool getTeam();

private:
	int id;
	Cell cell;
	Color color;
	Type type;
	Antenna antenna;
	Dir dir;
	bool sick;
};

#endif
