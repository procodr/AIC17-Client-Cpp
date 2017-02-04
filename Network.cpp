/*
 * Network.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: rmin
 */

#include "Network.h"
#include "util.h"
#include <chrono>
#include "Controller.h"

Network::Network(Controller* controller) {
// TODO Auto-generated constructor stub
	sockfd = -1;
	server = NULL;
	this->controller = controller;
	isConnected = false;
	isTerminated = false;
}

void Network::setConnectionData(std::string host, int port, std::string token) {
	this->host = host;
	this->port = port;
	this->token = token;
}

void Network::connect()
{
	try
	{
		isConnected = false;
		this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (this->sockfd < 0)
			throw("ERROR opening socket");
		this->server = gethostbyname(this->host.c_str());
		if (server == NULL)
		{
			throw("ERROR, no such host\n");
		}
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
		serv_addr.sin_port = htons(port);
		if (::connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
			throw("ERROR connecting");

		Message msg;
		msg.addNode(Constants::MESSAGE_KEY_NAME, Constants::MESSAGE_KEY_TOKEN);
		std::vector<std::string> tmp;
		tmp.push_back(token);
		msg.addArray("args", tmp);
		this->sendMessage(msg);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}
	catch (...) {
		return;
	}
	isConnected = true;
	isTerminated = false;
	startReceiving();
}

void Network::startReceiving()
{
	while (isConnected && !isTerminated)
	{
		if (!doReceive())
			break;
	}
	terminate();
}

bool Network::doReceive()
{
	try
	{
		char buf[MAX_LEN_OF_TCP];
		bzero(buf,MAX_LEN_OF_TCP);
		int sizeMessage = read(sockfd,buf,MAX_LEN_OF_TCP);
		if (sizeMessage <= 0)
			return false;
		SubPacket *cache = new SubPacket(MAX_LEN_OF_TCP);
		packets.push_back(cache);
		for (int i = 0; i < sizeMessage; i++)
		{
			if (buf[i] != '\0')
			{
				packets[packets.size() - 1]->push(buf[i]);
			}
			else
			{
				parse();
				packets.push_back(new SubPacket(MAX_LEN_OF_TCP));
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
	return true;
}

void Network::parse()
{
	std::string str;
	for (int i = 0; i < (int) packets.size(); i++)
	{
		str.append(packets[i]->buffer.begin(),
				   packets[i]->buffer.begin() + packets[i]->index);
	}

	Message msg;
	msg.setJson(str);

	controller->handleMessage(msg);

	clearPacket();
}

void Network::clearPacket()
{
	for (int i = 0; i < (int) packets.size(); i++)
		delete packets[i];
	packets.clear();
}

void Network::sendMessage(Message &msg)
{
	int n = -1;
	while (n < 0)
	{
		std::string message = msg.getJson();
		n = write(sockfd,message.c_str(),message.size());
	}
}

void Network::terminate() {
	isTerminated = true;
	isConnected = false;
	if(sockfd >= 0) {
		close(sockfd);
		sockfd = -1;
	}
}

Network::~Network() {
	terminate();
// TODO Auto-generated destructor stub
}

bool Network::getIsConnected() {
	return isConnected;
}

bool Network::getIsTerminated() {
	return isTerminated;
}
