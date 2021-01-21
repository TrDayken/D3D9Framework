#include "GhostPlatform.h"

GhostPlatform::GhostPlatform()
{
	EntityTag = Tag::platform;

	ColTag = Collision2DTag::Top;

	setRenderOrder(3);
}

void GhostPlatform::Render(Camera* camera)
{
	RenderBoundingBox(camera);
}

void GhostPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + width;
	b = this->Position.y + height;
}
