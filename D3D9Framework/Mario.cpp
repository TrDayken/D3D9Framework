#include "Mario.h"

Mario::Mario(float x, float y)
{
	this->start_x = x; 
	this->start_y = y;
}

void Mario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects)
{
}

void Mario::Render()
{
}

void Mario::SetState(int state)
{
}

void Mario::Reset()
{
}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
