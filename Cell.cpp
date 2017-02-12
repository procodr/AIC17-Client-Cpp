/*
 * Cell.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: armin
 */

#include "Cell.h"
#include "Entity.h"
#include "Slippers.h"
#include "Teleport.h"
#include "Beetle.h"
#include "util.h"

Cell::Cell(int row, int col) : row(row), col(col) {
	entity = nullptr;
}

Cell::~Cell() {
	if(entity != nullptr)
		delete entity;
}

void Cell::setEntity(Entity* entity) {
	if(this->entity != nullptr) {
		CERR("possibility of memory leakage\n");
	}
	this->entity = entity;
}

void Cell::delEntity() {
	if(this->entity == nullptr)
		return;
	delete(this->entity);
	this->entity = nullptr;
}

Entity* Cell::getEntity() {
	return this->entity;
}

Beetle* Cell::getBeetle() {
	if(this->entity == nullptr)
		return nullptr;
	return dynamic_cast<Beetle*> (this->entity);
}

Slippers* Cell::getSlipper() {
	return dynamic_cast<Slippers*> (this->entity);
}

Entity* Cell::getItem() {
	return this->entity;
}

Teleport* Cell::getTeleport() {
	return dynamic_cast<Teleport*> (this->entity);
}

void Cell::setPosition(int row, int col) {
	this->row = row;
	this->col = col;
}
