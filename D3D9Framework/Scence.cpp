#include "Scence.h"

Scence::Scence()
{
}

Scence::Scence(std::string id, std::string mappath, std::string filePath)
{
	this->id = id;
	this->mapPath = mappath;
	this->sceneFilePath = filePath;
}