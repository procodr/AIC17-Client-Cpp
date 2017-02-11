#include "Beetle.h"

Beetle::Beetle(int id, Cell pos, Direction dir, bool wing, BeetleType beetle_type, bool sick, int team_id)
    : Entity(id, pos), dir(dir), wing(wing), sick(sick), beetle_type(beetle_type), team_id(team_id) {};

BeetleType Beetle::getBeetleType() {
	return this->beetle_type;
}

bool Beetle::has_wing() {
	return wing;
}

Direction Beetle::getDirection() {
	return this->dir;
}

bool Beetle::is_sick() {
	return this->sick;
}

void Beetle::doMove(Move move, Size size) {
	int width = size.width;
	int height = size.height;
	switch (move) {
	case Move::RIGHT:
		this->dir = static_cast<Direction>((static_cast<int>(this->dir) + 3) % 4);
		break;
	case Move::LEFT:
		this->dir = static_cast<Direction>((static_cast<int>(this->dir) + 1) % 4);
		break;
	case Move::FORWARD:
		switch (this->dir) {
		case Direction::LEFT:
			if (this->pos.col > 0)
				this->pos.col -= 1;
			else
				this->pos.col = width - 1;
			break;
		case Direction::DOWN:
			this->pos.row = (this->pos.row + 1) % height;
			break;
		case Direction::RIGHT:
			this->pos.col = (this->pos.col + 1) % width;
			break;
		case Direction::UP:
			if (this->pos.row > 0)
				this->pos.row = this->pos.row - 1;
			else
				this->pos.row = height - 1;
			break;
		}
		break;
	}
}

void Beetle::alter(bool sick, bool wing) {
	this->sick = sick;
	this->wing = wing;
}
