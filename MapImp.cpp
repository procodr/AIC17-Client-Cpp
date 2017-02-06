#include "MapImp.h"

MapImp::MapImp(Size size)
    : size(size),
      entityMap(size.w, std::vector<Entity *>(size.h, NULL)),
      darknessMap(size.w, std::vector<int>(size.h, 0)),
      destMap(size.w, std::vector<Cell>(size.h, {0, 0}))
{
    for (int i = 0; i < size.w; i += 1)
		for (int j = 0; j < size.h; j += 1)
	    	destMap[i][j] = {i, j};
}

Entity *MapImp::getEntity(int x, int y)
{
    return entityMap[x][y];
}

bool MapImp::getShadow(int x, int y)
{
    return (darknessMap[x][y] > 0);
}

Cell MapImp::getDest(int x, int y)
{
    return destMap[x][y];
}

void MapImp::addEntity(Entity &entity)
{
    entityMap[entity.getPos().x][entity.getPos().y] = &entity;
}

void MapImp::delEntity(int x, int y)
{
    entityMap[x][y] = NULL;
}

void MapImp::changeShadow(int x, int y, int delta)
{
	for (int i = x - 1; i <= x + 1; i += 1)
		for (int j = y - 1; j <= y + 1; j += 1)
	    	if (0 <= i && i < size.w && 0 <= j && j < size.h)
				darknessMap[i][j] += delta;
}

void MapImp::addShadow(int x, int y)
{
    this->changeShadow(x, y, +1);
}

void MapImp::delShadow(int x, int y)
{
	this->changeShadow(x, y, -1);
}

void MapImp::addSewer(Sewer sewer)
{
	destMap[sewer.getPos().x][sewer.getPos().y].x = sewer.getDest().x;
    destMap[sewer.getPos().x][sewer.getPos().y].y = sewer.getDest().y;
}