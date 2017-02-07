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

EntityType Entity::getEntityType() const
{
    return this->entityType;
}

inline bool operator == (const Entity& lhs, const Entity& rhs)
{
	return lhs.getId() == rhs.getId();
}

void Entity::doMove(int x, int y)
{
	this->pos.row = x;
	this->pos.col = y;
}
