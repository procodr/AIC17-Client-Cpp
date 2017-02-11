#include <iostream>
#include "Map.h"
#include "util.h"
#include "Entity.h"
#include "Beetle.h"

Map::Map(Size size, int myId)
        : size(size), myId(myId) {
	table = new Cell**[size.height];
	for(int i = 0; i < size.height; i++)
		table[i] = new Cell*[size.width];
}

Map::~Map() {
	for(int i = 0; i < size.height; i++) {
		for(int j = 0; j < size.width; j++)
			delete(table[i][j]);
		delete[] table[i];
	}
	delete[] table;
}

Entity *Map::getEntity(int id) {
	if(this->allEntities.find(id) != this->allEntities.end())
		return allEntities[id];
	return nullptr;
}

void Map::addEntity(Entity *entity) {
	int id = entity->getId();
	this->allEntities.insert(PIE(id, entity));
	table[entity->getPosition().row][entity->getPosition().col]->setEntity(entity);
    switch(entity->getType()) {
    case EntityType::BEETLE:
    	if(entity->getTeamId() == this->myId)
    		this->myCells.push_back(table[entity->getPosition().row][entity->getPosition().col]);
    	else
    		this->oppCells.push_back(table[entity->getPosition().row][entity->getPosition().col]);
    	break;
    case EntityType::FOOD:
    	this->foodCells.push_back(table[entity->getPosition().row][entity->getPosition().col]);
    	break;
    case EntityType::SLIPPERS:
    	this->slipperCells.push_back(table[entity->getPosition().row][entity->getPosition().col]);
    	break;
    case EntityType::TRASH:
    	this->trashCells.push_back(table[entity->getPosition().row][entity->getPosition().col]);
    	break;
    case EntityType::TELEPORT:
    	this->teleportCells.push_back(table[entity->getPosition().row][entity->getPosition().col]);
    	break;
    }
}

void Map::delEntity(int id) {
	if(allEntities.find(id) == allEntities.end()) {
		throw("entity for deleting doesn't exist!!\n");
		return;
	}

	Cell pos = allEntities[id]->getPosition();
	int x = pos.row;
	int y = pos.col;
	if(table[x][y] == NULL) {
		throw("entity for deleting doesn't exist!!\n");
		return;
	}
    if (table[x][y]->getEntity()->getId() == id) {
    	Entity* entity = table[x][y]->getEntity();
    	switch(entity->getType()) {
    	case EntityType::BEETLE:
    		if(entity->getTeamId() == this->myId) {
    			for(int i = 0; i < (int)this->myCells.size(); i++)
    				if(myCells[i]->getEntity() == entity) {
    					myCells.erase(myCells.begin() + i);
    					break;
    				}
    		}
    		else {
    			for(int i = 0; i < (int)this->oppCells.size(); i++)
    				if(oppCells[i]->getEntity() == entity) {
    					oppCells.erase(oppCells.begin() + i);
    					break;
    				}
    		}
    		break;
    	case EntityType::FOOD:
    		for(int i = 0; i < (int)this->foodCells.size(); i++)
    			if(foodCells[i]->getEntity() == entity) {
    				foodCells.erase(foodCells.begin() + i);
    				break;
    			}
    		break;
    	case EntityType::SLIPPERS:
    		for(int i = 0; i < (int)this->slipperCells.size(); i++)
    			if(slipperCells[i]->getEntity() == entity) {
    				slipperCells.erase(slipperCells.begin() + i);
    				break;
    			}
    		break;
    	case EntityType::TRASH:
    		for(int i = 0; i < (int)this->trashCells.size(); i++)
    			if(trashCells[i]->getEntity() == entity) {
    				trashCells.erase(trashCells.begin() + i);
    				break;
    			}
    		break;
    	case EntityType::TELEPORT:
    		for(int i = 0; i < (int)this->teleportCells.size(); i++)
    			if(teleportCells[i]->getEntity() == entity) {
    				teleportCells.erase(teleportCells.begin() + i);
    				break;
    			}
    		break;
    	}
    	table[x][y]->delEntity();
    	this->allEntities.erase(id);
    }
}

void Map::moveEntity(int id, Move move) {
	if(allEntities.find(id) == allEntities.end()) {
		throw("entity for moving doesn't exist!!\n");
	}
	Beetle* beetle = dynamic_cast<Beetle*> (allEntities[id]);
	beetle->doMove(move, this->size);
}

void Map::moveEntity(int id, int x, int y, bool wing, bool sick) {

}

int Map::getWidth() {
	return this->size.width;
}

int Map::getHeight() {
	return this->size.height;
}

std::vector<Cell*> Map::getMyCells() {
	return this->myCells;
}

std::vector<Cell*> Map::getOppCells() {
	return this->oppCells;
}

std::vector<Cell*> Map::getTeleportCells() {
	return this->teleportCells;
}

std::vector<Cell*> Map::getSlipperCells() {
	return this->slipperCells;
}

std::vector<Cell*> Map::getTrashCells() {
	return this->trashCells;
}

std::vector<Cell*> Map::getFoodCells() {
	return this->foodCells;
}
