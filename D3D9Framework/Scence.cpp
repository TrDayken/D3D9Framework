#include "Scence.h"

Scence::Scence()
{
}

Scence::Scence(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneFilePath = filePath;
}