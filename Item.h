#ifndef ITEM_H
#define ITEM_H

#include "Types.h"

#include <vector>

using namespace aic;

class Item {
private:
	int id;
	Cell pos;

public:
	Item(int id, Cell pos);
	virtual ~Item();

	int getId();
	Cell getPos();
};

#endif /* ITEM_H */
