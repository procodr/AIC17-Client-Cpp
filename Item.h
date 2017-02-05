#ifndef ITEM_H
#define ITEM_H

#include "Types.h"

#include <vector>

using namespace aic;

class Item {
private:
	int id;
	Cell pos;
	ItemType type;

public:
	Item(int id, Cell pos, ItemType type);
	virtual ~Item();

	int getId();
	Cell getPos();
	ItemType getType();
};

#endif /* ITEM_H */
