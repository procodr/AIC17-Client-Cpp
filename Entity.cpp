#include "Entity.h"

Entity::Entity(int id, Cell* cell, EntityType type) :
		id(id), cell(cell), entityType(type) {
	creationTurn = globalTurn;
	cell->setEntity(this);
}

Entity::~Entity() {
}

int Entity::getId() const
{
	return this->id;
}

Cell* Entity::getPosition() const
{
	return this->cell;
}

EntityType Entity::getType() const
{
    return this->entityType;
}

inline bool operator == (const Entity& lhs, const Entity& rhs)
{
	return lhs.getId() == rhs.getId();
}

Cell* Entity::getCell() const {
	return this->cell;
}

void Entity::setPosition(int row, int col) {
	this->cell->setPosition(row, col);
}
