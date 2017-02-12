#include <sstream>
#include <iostream>
#include "Map.h"
#include "util.h"
#include "Entity.h"
#include "Beetle.h"

Map::Map(Size size, int myId)
        : size(size), myId(myId) {
//	table = new Cell**[size.height];
//	for(int i = 0; i < size.height; i++) {
//		table[i] = new Cell*[size.width];
//		for(int j = 0; j < size.width; j++)
//			table[i][j] = nullptr;
////			table[i][j] = new Cell(i, j);
//	}
}

Map::~Map() {
//	for(int i = 0; i < size.height; i++) {
//		for(int j = 0; j < size.width; j++) {
//
//			delete(table[i][j]);
//		}
//		delete[] table[i];
//	}
//	delete[] table;
}

Entity *Map::getEntity(int id) {
	if(this->allEntities.find(id) != this->allEntities.end())
		return allEntities[id];
	return nullptr;
}

void Map::addEntity(Entity *entity) {
	int id = entity->getId();
	this->allEntities.insert(PIE(id, entity));
//	table[entity->getPosition().row][entity->getPosition().col]->setEntity(entity);
//	Cell* newCell = new Cell(entity->getPosition().row, entity->getPosition().col);
    switch(entity->getType()) {
    case EntityType::BEETLE:
//    	table[entity->getPosition().row][entity->getPosition().col] = newCell;
//    	newCell->setEntity(entity);
    	if(dynamic_cast<Beetle*>(entity)->getTeamId() == this->myId)
    		this->myCells.push_back(entity->getCell());
    	else
    		this->oppCells.push_back(entity->getCell());
    	break;
    case EntityType::FOOD:
//    	table[entity->getPosition().row][entity->getPosition().col] = newCell;
//    	newCell->setEntity(entity);
    	this->foodCells.push_back(entity->getCell());
    	break;
    case EntityType::SLIPPERS:
    	this->slipperCells.push_back(entity->getCell());
    	break;
    case EntityType::TRASH:
//    	table[entity->getPosition().row][entity->getPosition().col] = newCell;
//    	newCell->setEntity(entity);
    	this->trashCells.push_back(entity->getCell());
    	break;
    case EntityType::TELEPORT:
    	this->teleportCells.push_back(entity->getCell());
    	break;
    }
}

void Map::delEntity(int id) {
	if(allEntities.find(id) == allEntities.end()) {
		throw("entity for deleting doesn't exist!!\n");
		return;
	}

	Entity* entity = allEntities[id];

//    if (table[x][y]->getEntity()->getId() == id) {
//    	Entity* entity = table[x][y]->getEntity();
//	int row, col;
	switch (entity->getType()) {
	case EntityType::BEETLE:
		if (dynamic_cast<Beetle*>(entity)->getTeamId() == this->myId) {
			for (int i = 0; i < (int) this->myCells.size(); i++)
				if (myCells[i]->getEntity() == entity) {
//					row = myCells[i]->row;
//					col = myCells[i]->col;
					delete(myCells[i]);
					myCells.erase(myCells.begin() + i);
					break;
				}
		} else {
			for (int i = 0; i < (int) this->oppCells.size(); i++)
				if (oppCells[i]->getEntity() == entity) {
//					row = oppCells[i]->row;
//					col = oppCells[i]->col;
					delete(oppCells[i]);
					oppCells.erase(oppCells.begin() + i);
					break;
				}
		}
//		delete(table[row][col]);
//		table[row][col] = nullptr;
		break;
	case EntityType::FOOD:
		for (int i = 0; i < (int) this->foodCells.size(); i++)
			if (foodCells[i]->getEntity() == entity) {
//				row = foodCells[i]->row;
//				col = foodCells[i]->col;
				delete(foodCells[i]);
				foodCells.erase(foodCells.begin() + i);
				break;
			}
//		delete(table[row][col]);
//		table[row][col] = nullptr;
		break;
	case EntityType::SLIPPERS:
		for (int i = 0; i < (int) this->slipperCells.size(); i++)
			if (slipperCells[i]->getEntity() == entity) {
				delete(slipperCells[i]);
				slipperCells.erase(slipperCells.begin() + i);
				break;
			}
		break;
	case EntityType::TRASH:
		for (int i = 0; i < (int) this->trashCells.size(); i++)
			if (trashCells[i]->getEntity() == entity) {
//				row = trashCells[i]->row;
//				col = trashCells[i]->col;
				delete(trashCells[i]);
				trashCells.erase(trashCells.begin() + i);
				break;
			}
//		delete(table[row][col]);
//		table[row][col] = nullptr;
		break;
	case EntityType::TELEPORT:
		for (int i = 0; i < (int) this->teleportCells.size(); i++)
			if (teleportCells[i]->getEntity() == entity) {
				delete(teleportCells[i]);
				teleportCells.erase(teleportCells.begin() + i);
				break;
			}
		break;
	}
//    	table[x][y]->delEntity();
	this->allEntities.erase(id);
//    }
}

void Map::moveEntity(int id, Move move) {
	if(allEntities.find(id) == allEntities.end()) {
		std::stringstream str;
		str << "entity " << id << " for moving doesn't exist!!\n";
		throw(str.str());
	}
	Beetle* beetle = dynamic_cast<Beetle*> (allEntities[id]);
	beetle->doMove(move, this->size);
}

void Map::moveEntity(int id, int row, int col, bool wing, bool sick) {
	if(this->allEntities.find(id) == this->allEntities.end()) {
		throw("entity for moving doesn't exist!!\n");
	}
	Beetle* beetle = dynamic_cast<Beetle*> (allEntities[id]);
	beetle->setPosition(row, col);
	beetle->setWing(wing);
	beetle->setSick(sick);
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
