#include "AbstractFXObject.h"
#include "ScenceManager.h"

AbstractFXObject::AbstractFXObject()
{
	Animation_created = GetTickCount();
}

void AbstractFXObject::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (GetTickCount() - Animation_created > ANIMATIONTIME)
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);

}

void AbstractFXObject::setStartPosition(Vector2 pos)
{
	this->Position = pos; 
}

void AbstractFXObject::Render(Camera* camera)
{
	GameObject::Render(camera); 
}

void AbstractFXObject::setForce(Vector2 force)
{
	this->Force = force;
}
