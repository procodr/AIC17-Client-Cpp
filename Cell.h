/*
 * Cell.h
 *
 *  Created on: Feb 11, 2017
 *      Author: armin
 */

#ifndef CELL_H_
#define CELL_H_

class Entity;
class Beetle;
class Slippers;
class Teleport;

class Cell {
	Entity* entity;
public:
	int row, col;
	Cell(int row, int col);
	virtual ~Cell();

	void setEntity(Entity* entity);
	Entity* getEntity();
	void delEntity();

	Beetle* getBeetle();
	Slippers* getSlipper();
	Entity* getItem();
	Teleport* getTeleport();

	void setPosition(int row, int col);
};

#endif /* CELL_H_ */
