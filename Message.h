/*
 * Message.h
 *
 *  Created on: Feb 4, 2015
 *      Author: rmin
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>

#include <json/json.h>

#include <map>
#include <vector>
#include <string>
#include <sstream>

class Message {
private:
	Json::Value root;
	Json::Reader reader;
	Json::StyledWriter writer;
public:
	Message();
	virtual ~Message();
	void setJson(std::string &str);
	std::string getJson();
	void addNode(std::string name,std::string value);
	void addNode(std::string name,int value);
	void addArray(std::string name,std::vector<int> value);
	void addArray(std::string name,std::vector<std::string> value);
	void addArray(std::string name, std::vector<Message> value);
	std::string getName();
	Json::Value& getRoot();
	void setJson(Json::Value value);
	Json::Value& getArray(std::string str,bool isTurn = 0);
};

#endif /* MESSAGE_H_ */
