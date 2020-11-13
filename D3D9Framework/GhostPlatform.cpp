#include "GhostPlatform.h"

GhostPlatform::GhostPlatform()
{
	EntityTag = Tag::platform;

	ColTag = Collision2DTag::Top;
}

void GhostPlatform::Render(Camera* camera)
{
	RenderBoundingBox(camera);
}

void GhostPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
