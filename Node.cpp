/*
 * Node.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: armin
 */

#include "Node.h"

Node::Node(int index) {
	// TODO Auto-generated constructor stub
	this->index = index;
	this->owner = -1;
	this->armyCount = 0;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

std::vector<Node*>& Node::getNeighbours() {
	return this->neighbours;
}

int Node::getIndex() {
	return this->index;
}

int Node::getOwner() {
	return this->owner;
}

int Node::getArmyCount() {
	return this->armyCount;
}

void Node::setNeighbours(const std::vector<Node*>& neighbours) {
	this->neighbours.clear();
	for(auto &neighbour : neighbours)
		this->neighbours.push_back(neighbour);
}

void Node::setOwner(int owner) {
    this->owner = owner;
}

void Node::setArmyCount(int armyCount) {
    this->armyCount = armyCount;
}

void Node::setIndex(int index) {
    this->index = index;
}
