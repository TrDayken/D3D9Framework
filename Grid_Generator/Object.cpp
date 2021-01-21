#include "Object.h"
#include <tgmath.h>

Object::Object()
{
}

Object::Object(TiXmlElement* XMLobject, int cellwidth, int cellheight)
{
	XMLobject->QueryIntAttribute("id", &this->id);

	XMLobject->QueryIntAttribute("x", &this->x);
	XMLobject->QueryIntAttribute("y", &this->y);

	this->width = 0;
	this->height = 0;

	XMLobject->QueryIntAttribute("x", &this->x);
	XMLobject->QueryIntAttribute("y", &this->y);

	XMLobject->QueryIntAttribute("width", &this->width);
	XMLobject->QueryIntAttribute("height", &this->height);

	this->cellx = (int)(x / cellwidth);
	this->celly = (int)(y / cellheight);

	float z = (float)(x + width) / cellwidth;
	float u = (float)(y + height) / cellheight;

	this->spanx = ceil(z) - cellx;
	this->spany = ceil(u) - celly;

}

Object::~Object()
{
}

int Object::getID()
{
	return this->id;
}

int Object::getX()
{
	return this->x;
}

int Object::getY()
{
	return this->y;
}

int Object::getWidth()
{
	return this->width;
}

int Object::getHeight()
{
	return this->height;
}

int Object::getCellx()
{
	return this->cellx;
}

int Object::getCelly()
{
	return this->celly;
}

int Object::getSpanx()
{
	return this->spanx;
}

int Object::getSpany()
{
	return this->spany;
}

void Object::setID(int id)
{
	this->id = id;
}

void Object::setX(int x)
{
	this->x = x; 
}

void Object::setY(int y)
{
	this->y = y;
}

void Object::setWidth(int w)
{
	this->width = w;
}

void Object::setHeight(int h)
{
	this->height = h;
}
