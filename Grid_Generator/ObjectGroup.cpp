#include "ObjectGroup.h"

void ObjectGroup::setID(int id)
{
	this->id = id;
}

int ObjectGroup::getID()
{
	return this->id;
}

void ObjectGroup::setName(std::string name)
{
	this->name = name; 
}

std::string ObjectGroup::getName()
{
	return this->name;
}

void ObjectGroup::AddObject(Object* obj)
{
	objects.push_back(obj);
}

std::vector<Object*> ObjectGroup::getObject()
{
	return this->objects;
}
