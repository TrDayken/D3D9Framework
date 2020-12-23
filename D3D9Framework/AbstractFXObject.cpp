#include "AbstractFXObject.h"
#include "ScenceManager.h"

AbstractFXObject::AbstractFXObject()
{
	Animation_created = GetTickCount();
}

void AbstractFXObject::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount() - Animation_created > ANIMATIONTIME)
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);

}

void AbstractFXObject::setStartPosition(Vector2 pos)
{
	this->startPosition = pos; 
}
