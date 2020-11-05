#include "InvisibleBrick.h"

void InvisibleBrick::Render(Camera* camera)
{
	Vector2 pos = camera->toCameraPosistion(x, y);
	AnimationManager::GetInstance()->GetAnimation("ani-small-mario-hold")->Render(pos.x, pos.y);
	
}

void InvisibleBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
