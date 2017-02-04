#include "Fish.h"

Fish::Fish(int id, int x, int y, bool color, bool queen, bool sick, bool team) :
    id(id), x(x), y(y), color(color), queen(queen), sick(sick), team(team) {};

int Fish::getId() {
    return this->id;
}

pair<int, int> Fish::getPos() {
    return make_pair(this->x, this->y);
}

bool Fish::getColor() {
    return this->color;
}

bool Fish::isQueen() {
    return this->queen;
}

bool Fish::isSick() {
    return this->sick;
}

bool Fish::getTeam() {
    return this->team;
}