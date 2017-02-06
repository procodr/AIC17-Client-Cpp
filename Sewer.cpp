#include "Sewer.h"

Sewer::Sewer(int id, Cell pos, Cell destination) : Entity(id, pos), destination(destination) {};

int Sewer::getDestination(){
	return this->destination;
}
