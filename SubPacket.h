/*
 * SubPacket.h
 *
 *  Created on: Feb 17, 2015
 *      Author: rmin
 */

#ifndef SUBPACKET_H_
#define SUBPACKET_H_

#include <string>

class SubPacket {
	SubPacket();
public:
	int size;
	int index;
	std::string buffer;
	SubPacket(int size);
	virtual ~SubPacket();
	void push(char c);
};

#endif /* SUBPACKET_H_ */
