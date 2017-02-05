#ifndef ROACH_H
#define ROACH_H

#include <utility>

class Fish {
public:
	Fish(int id, int x, int y, bool color, bool queen, bool sick, bool team);

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
