/*
 * main.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: armin
 */

#include <iostream>
#include <cstdlib>
#include "Controller.h"

std::string argNames[4] = { "AICHostIP", "AICHostPort", "AICToken","AICRetryDelay" };
std::string argDefaults[4] = { "127.0.0.1", "7099", "00000000000000000000000000000000", "1000" };

int main() {
	setbuf(stdout, NULL);

	std::string args[4];
	for (int i = 0; i < 4; i++) {
		char* tmp = std::getenv(argNames[i].c_str());
		if (tmp == NULL)
			args[i] = std::string(argDefaults[i]);
		else
			args[i] = tmp;
	}

	try {
		Controller *control = new Controller(args);
		control->start();
	} catch (std::exception& e) {
		std::cerr << "MAIN EXCEPTION\n";
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
