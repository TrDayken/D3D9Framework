#include <dinput.h>

#include "WarpEntrance.h"

WarpEntrance::WarpEntrance()
{
	this->EntityTag = Tag::entrance;

	this->ColTag = Collision2DTag::None;
}

void WarpEntrance::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + width; 
	b = this->Position.y + height;
}

void WarpEntrance::OnOverLap(GameObject* obj)
{

}

void WarpEntrance::setWarpDirection(WarpDirection dir)
{
	this->dir = dir;
}

WarpDirection WarpEntrance::getWarpDirection()
{
	return this->dir;
}

void WarpEntrance::Render(Camera* camera)
{
	GameObject::Render(camera);

	RenderBoundingBox(camera);
}

int WarpEntrance::getKeyDirection()
{
	int warpKey;
	switch (this->getWarpDirection())
	{
	case WarpDirection::left: warpKey = DIK_LEFT; break;
	case WarpDirection::up: warpKey = DIK_UP; break;
	case WarpDirection::right: warpKey = DIK_RIGHT; break;
	case WarpDirection::down: warpKey = DIK_DOWN; break;
	}

	return warpKey;
}
