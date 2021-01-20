#pragma once


#include <string> 
#include <vector>

#include "Object.h"

class ObjectGroup
{
	int id;
	std::string name;

	std::vector<Object*> objects;
public: 

	void setID(int id);
	int getID();

	void setName(std::string name);
	std::string getName();

	void AddObject(Object* obj);
	std::vector<Object*> getObject();
};

