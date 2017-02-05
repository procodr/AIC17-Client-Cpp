#include "Map.h"

Map::Map(Size size)
    : size(size),
      entityMap(size.w, vector<Entity *>(size.h, NULL)),
      darknessMap(size.w, vector<int>(size.h, 0)),
      destMap(size.w, vector<int>(size.h, {0, 0}))
{
    for (int i = 0; i < size.w; i += 1)
		for (int j = 0; j < size.h; j += 1)
	    	destMap[i][j] = {i, j};
}

Entity *Map::getEntity(int x, int y)
{
    return entityMap[x][y];
}

bool Map::getShadow(int x, int y)
{
    return (darknessMap[x][y] > 0);
}

Cell Map::getDest(int x, int y)
{
    return destMap[x][y];
}

void Map::addEntity(const Entity &entity)
{
    entityMap[entity.getPos().x][entity.getPos().y] = &entity;
}

void Map::delEntity(int x, int y)
{
    entityMap[x][y] = NULL;
}

void Map::changeShadow(int x, int y, int delta)
{
	for (int i = x - 1; i <= x + 1; i += 1)
		for (int j = y - 1; j <= y + 1; j += 1)
	    	if (0 <= i && i < size.w && 0 <= j && j < size.h)
				darknessMap[i][j] += delta;
}

void Map::addShadow(int x, int y)
{
    this->changeShadow(x, y, +1);
}

void Map::delShadow(int x, int y)
{
	this->changeShadow(x, y, -1);
}

void Map::addTeleport(Teleport teleport)
{
	destMap[teleport.a.x][teleport.a.y] = teleport.b;
	destMap[teleport.b.x][teleport.b.y] = teleport.a;
}