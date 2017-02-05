#include "Entity.h"

Entity::Entity(int id, Cell pos) : id(id), pos(pos) {}

virtual Entity::~Entity() {};

int Entity::getId()
{
	return this->id;
}

Cell Entity::getPos()
{
	return this->pos;
}
