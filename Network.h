/*
 * Network.h
 *
 *  Created on: Feb 4, 2015
 *      Author: rmin
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#define MAX_LEN_OF_TCP 66000

#include "Message.h"
#include <vector>
#include "SubPacket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Controller;

class Network {
	std::vector<SubPacket*> packets;
	bool isTerminated;
	int port;
	std::string host;
	std::string token;
	bool isConnected;
	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	bool doReceive();
	void startReceiving();
	Controller* controller;
public:
	Network(Controller* controller);
	void sendMessage(Message &msg);
	void parse();
	void terminate();
	void setConnectionData(std::string host,int port,std::string token);
	void connect();
	virtual ~Network();
	bool getIsConnected();
	bool getIsTerminated();
	void clearPacket();
};

#endif /* NETWORK_H_ */
