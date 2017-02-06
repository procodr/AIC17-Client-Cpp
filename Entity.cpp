#include "Entity.h"

Entity::Entity(int id, Cell pos) : id(id), pos(pos) {}

Entity::~Entity() {};

int Entity::getId() const
{
	return this->id;
}

Cell Entity::getPos() const
{
	return this->pos;
}
