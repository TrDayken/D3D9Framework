#pragma once


#include <string> 
#include <vector>

#include "Object.h"
#include "tinyXML/tinyxml/tinyxml.h"

class ObjectGroup
{
	int id;
	std::string name;

	std::vector<Object*> objects;
public: 
	ObjectGroup();
	ObjectGroup(TiXmlElement* XMLobjectgroup, int cellwidth, int cellheight);
	~ObjectGroup();


	void setID(int id);
	int getID();

	void setName(std::string name);
	std::string getName();

	void AddObject(Object* obj);
	std::vector<Object*> getObject();
};

