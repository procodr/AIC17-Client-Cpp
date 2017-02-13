/*
 * Controller.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: rmin
 */

#include "Controller.h"
#include "util.h"
#include "Network.h"
#include <chrono>
#include "unistd.h"

void usleep(__int64 usec)
{
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}

int toInt(std::string str) {
	int ans=0;
	for(int i = 0; i < (int)str.size(); i++) {
		ans*=10;
		ans+=str[i]-'0';
	}
	return ans;
}

Controller::Controller(std::string *args)
{
	ip = args[0];
	port = toInt(args[1]);
	token = args[2];
	retryDelay = toInt(args[3]);
	time = 0;
	eventHandler = NULL;
	game = NULL;
	network = NULL;
	client = NULL;
}

Controller::~Controller()
{
	if (eventHandler != NULL)
		delete eventHandler;
	if (game != NULL)
		delete game;
	if (network != NULL)
		delete network;
	if (client != NULL)
		delete client;
}

void Controller::start()
{
	try
	{
		network = new Network(this);
		network->setConnectionData(ip, port, token);
		eventHandler = new EventHandler(network);
		game = new Game();
		client = new AI();
		int counter = 0;
		while (counter < 3 && network != NULL && !network->getIsConnected())
		{
			counter++;
			std::cerr << "Trying to connect #" << counter << std::endl;
			network->connect();
			if (network->getIsTerminated() == true)
				break;
			usleep(retryDelay * 1000);
		}

		std::cerr << "Connection Terminated" << std::endl;
	}
	catch (const char* str)
	{
		std::cerr << str << std::endl;
	}
	catch (std::string &str) {
		std::cerr << str << std::endl;
	}
}

void Controller::handleMessage(Message &msg)
{
	if (msg.getName() == Constants::MESSAGE_KEY_TURN)
	{
		handleTurnMessage(msg);
	}
	else if (msg.getName() == Constants::MESSAGE_KEY_INIT)
	{
		handleInitMessage(msg);
	}
	else if (msg.getName() == Constants::MESSAGE_KEY_SHUTDOWN
			|| msg.getName() == Constants::MESSAGE_KEY_WRONG_TOKEN)
	{
		network->terminate();
	}
}

void Controller::handleTurnMessage(Message &msg) {
	game->handleTurnMessage(msg);
	doTurn();
}

void Controller::handleInitMessage(Message &msg) {
	game->handleInitMessage(msg);
}

void Controller::run()
{
	client->doTurn(game);
}

void Controller::doTurn()
{
	try
	{
		std::thread thr(&Controller::run, this);
		thr.detach();
 	}
	catch (...)
	{
		std::cerr << "Exception in Controller::doTurn" << std::endl;
	}
}
