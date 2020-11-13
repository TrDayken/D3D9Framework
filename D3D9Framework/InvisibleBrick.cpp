#include "InvisibleBrick.h"

InvisibleBrick::InvisibleBrick()
{
	ColTag = Collision2DTag::FourSide;
	EntityTag = Tag::platform;
}

void InvisibleBrick::Render(Camera* camera)
{
	RenderBoundingBox(camera);
}

void InvisibleBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
