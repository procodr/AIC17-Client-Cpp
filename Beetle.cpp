#include "Beetle.h"

Beetle::Beetle(int id, Cell* cell, Direction dir, bool wing, BeetleType beetle_type, bool sick, int team_id)
    : Entity(id, cell, EntityType::BEETLE), dir(dir), wing(wing), sick(sick), beetle_type(beetle_type), team_id(team_id) {
};

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
			if (this->cell->col > 0)
				this->cell->col -= 1;
			else
				this->cell->col = width - 1;
			break;
		case Direction::DOWN:
			this->cell->row = (this->cell->row + 1) % height;
			break;
		case Direction::RIGHT:
			this->cell->col = (this->cell->col + 1) % width;
			break;
		case Direction::UP:
			if (this->cell->row > 0)
				this->cell->row = this->cell->row - 1;
			else
				this->cell->row = height - 1;
			break;
		}
		break;
	}
}

void Beetle::alter(bool sick, bool wing) {
	this->sick = sick;
	this->wing = wing;
}

int Beetle::getTeamId() {
	return team_id;
}

void Beetle::setSick(bool sick) {
	this->sick = sick;
}

void Beetle::setWing(bool wing) {
	this->wing = wing;
}
