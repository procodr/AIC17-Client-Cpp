#include "Entity.h"

Entity::Entity(int id, Cell pos, EntityType type) :
		id(id), pos(pos), entityType(type) {
	creationTurn = globalTurn;
}

Entity::~Entity() {
}

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
