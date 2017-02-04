/*
 * Json.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: rmin
 */

#include "Message.h"
#include <chrono>

Message::Message() {
	// TODO Auto-generated constructor stub
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

void Message::setJson(std::string &str)
{
	reader.parse(str, root, false);
}

std::string Message::getJson() {
	std::string output = writer.write(root);
	output.push_back('\0');
	return output;
}

void Message::setJson(Json::Value value) {
	this->root = value;
}

std::string Message::getName() {
	return root["name"].asString();
}

void Message::addNode(std::string name, std::string value) {
	root[name] = value;
}

void Message::addNode(std::string name, int value) {
	root[name] = value;
}

void Message::addArray(std::string name, std::vector<int> value) {
	if (value.size() == 0) {
		root[name] = Json::Value(Json::arrayValue);
	} else {
		for (int i = 0; i < (int) value.size(); i++) {
			Json::Value tmp(value[i]);
			root[name].append(tmp);
		}
	}
}

void Message::addArray(std::string name, std::vector<std::string> value) {
	if (value.size() == 0) {
		root[name] = Json::Value(Json::arrayValue);
	} else {
		for (int i = 0; i < (int) value.size(); i++) {
			Json::Value tmp(value[i]);
			root[name].append(tmp);
		}
	}
}

void Message::addArray(std::string name, std::vector<Message> value) {
	if (value.size() == 0) {
		root[name] = Json::Value(Json::arrayValue);
	} else {
		for (int i = 0; i < (int) value.size(); i++) {
			Json::Value tmp(value[i].getRoot());
			root[name].append(tmp);
		}
	}
}

Json::Value& Message::getArray(std::string str, bool isTurn) {
	return root[str];
}

Json::Value& Message::getRoot() {
	return root;
}
