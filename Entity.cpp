#include "Entity.h"

Entity::Entity() : id(-1), pos({-1, -1}) {}

Entity::Entity(int id, Cell pos) : id(id), pos(pos) {}

Entity::~Entity() {};

int Entity::getId() const
{
	return this->id;
}

Cell Entity::getPosition() const
{
	return this->pos;
}

EntityType Entity::getType() const
{
    return this->entityType;
}

inline bool operator == (const Entity& lhs, const Entity& rhs)
{
	return lhs.getId() == rhs.getId();
}

int Entity::getTeamId() const {
	return team_id;
}
