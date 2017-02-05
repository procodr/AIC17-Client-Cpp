#include "Item.h"

Item::Item(int id, Cell pos, ItemType type) : id(id), pos(pos), type(type) {}

virtual Item::~Item() {};

int Item::getId()
{
	return this->id;
}

Cell Item::getPos()
{
	return this->pos;
}

ItemType getType()
{
	return this->type;
}