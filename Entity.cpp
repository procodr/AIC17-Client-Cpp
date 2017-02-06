#include "Entity.h"

Entity::Entity() : id(-1), pos({-1, -1}) {}

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

inline bool operator == (const Entity& lhs, const Entity& rhs)
{
	return lhs.getId() == rhs.getId();
}