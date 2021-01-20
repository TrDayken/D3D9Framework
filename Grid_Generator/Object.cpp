#include "Object.h"

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
