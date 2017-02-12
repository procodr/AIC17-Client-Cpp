#include "Teleport.h"

Teleport::Teleport(int id, Cell* cell, int pairId) : Entity(id, cell, EntityType::TELEPORT), pairId(pairId) {
	pair = nullptr;
}

Teleport* Teleport::getPair()
{
	if(pair == nullptr) {
		throw("teleport's pair doesn't set");
	}
	return pair;
}

int Teleport::getPairId() {
	return pairId;
}

void Teleport::setPair(Teleport* pair) {
	this->pair = pair;
}
