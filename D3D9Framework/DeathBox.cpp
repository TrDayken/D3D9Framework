#include "DeathBox.h"
#include "Global_Variable.h"

DeathBox::DeathBox()
{
	this->EntityTag = Tag::dead;

	this->ColTag = Collision2DTag::None;
}

void DeathBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x; 
	t = this->Position.y;
	r = this->Position.x + width; 
	b = this->Position.y + height;
}

void DeathBox::OnOverLap(GameObject* obj)
{
}
