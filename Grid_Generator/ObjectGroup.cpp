#include "ObjectGroup.h"

ObjectGroup::ObjectGroup()
{
}

ObjectGroup::ObjectGroup(TiXmlElement* XMLobjectgroup,int cellwidth, int cellheight)
{
	XMLobjectgroup->QueryIntAttribute("id", &this->id);

	this->name = XMLobjectgroup->Attribute("name");

	for (TiXmlElement* XMLobject = XMLobjectgroup->FirstChildElement("object"); XMLobject != NULL; XMLobject = XMLobject->NextSiblingElement("object"))
	{
		this->AddObject(new Object(XMLobject,  cellwidth,  cellheight));
	}
}

ObjectGroup::~ObjectGroup()
{
}

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
