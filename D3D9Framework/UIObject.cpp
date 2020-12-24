#include "UIObject.h"

UIObject::UIObject()
{
	this->StaticPosition = VectorZero; 
}

UIObject::~UIObject()
{
	animation_set.clear();
}

void UIObject::setStaticPosition(Vector2 position)
{
	this->StaticPosition = position; 
}

Vector2 UIObject::getStaticPosition()
{
	return this->StaticPosition; 
}

void UIObject::AddAnimation(std::string name, LPANIMATION animation)
{
	animation_set[name] = animation;
}

void UIObject::Update(DWORD dt)
{
	this->dt = dt; 
}

void UIObject::Render()
{

}
