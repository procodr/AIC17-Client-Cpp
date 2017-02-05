#include "Item.h"

Item::Item(int id, Cell pos) : id(id), pos(pos) {}

virtual Item::~Item() {};

int Item::getId()
{
	return this->id;
}

Cell Item::getPos()
{
	return this->pos;
}
