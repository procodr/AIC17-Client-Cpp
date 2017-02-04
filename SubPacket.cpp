/*
 * SubPacket.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: rmin
 */

#include "SubPacket.h"
#include <iostream>

SubPacket::SubPacket() {
	index = size = 0;
}

SubPacket::SubPacket(int size) {
	// TODO Auto-generated constructor stub
	index = 0;
	this->size = size;
	buffer.resize(size);
}

SubPacket::~SubPacket() {
	// TODO Auto-generated destructor stub
}

void SubPacket::push(char c) {
	buffer[index++] = c;
}

