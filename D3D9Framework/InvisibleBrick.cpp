#include "InvisibleBrick.h"

InvisibleBrick::InvisibleBrick()
{
	ColTag = Collision2DTag::FourSide;
	EntityTag = Tag::platform;
}

void InvisibleBrick::Render(Camera* camera)
{
	//RenderBoundingBox(camera);
}

void InvisibleBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + width;
	b = this->Position.y + height;
}
