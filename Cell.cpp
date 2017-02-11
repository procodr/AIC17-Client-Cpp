/*
 * Cell.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: armin
 */

#include "Cell.h"
#include "Entity.h"
#include "Beetle.h"

Cell::Cell(int row, int col) : row(row), col(col) {
	entity = nullptr;
}

Cell::~Cell() {
	if(entity != nullptr)
		delete entity;
}

void Cell::setEntity(Entity* entity) {
	this->entity = entity;
}

void Cell::delEntity() {
	if(this->entity == nullptr)
		return;
	delete(this->entity);
}

Entity* Cell::getEntity() {
	return this->entity;
}

Beetle* Cell::getBeetle() {
	if(this->entity == nullptr)
		return nullptr;
	return dynamic_cast<Beetle*> (this->entity);
}

Entity* Cell::getSlipper() {
	return this->entity;
}

Entity* Cell::getItem() {
	return this->entity;
}

Entity* Cell::getTeleport() {
	return this->entity;
}
