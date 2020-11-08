#include "FireShoot.h"


FireShoot::FireShoot(float x, float y, int direction)
{
	EntityTag = Tag::projectile;
	this->x = x;
	this->y = y;
	vx = direction * BULLET_VX;
	LoadAnimation();
}

void FireShoot::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(x, y);

	string ani = ANI_BULLET;

	animation_set[ani]->Render(camPos.x, camPos.y, direction);
}

void FireShoot::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}

void FireShoot::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation(ANI_BULLET, animation->GetAnimation(ANI_BULLET));
}

void FireShoot::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	vy += BULLET_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4;
		y += min_ty * dy + ny * 0.4;
		if (ny < 0) vy = -BULLET_BOUNCE;


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->EntityTag == Tag::enemy) // if e->obj is Goomba 
			{
				LPGAMEOBJECT obj = e->obj;
				obj->CollisionObject(this, e->nx, e->ny);
				ScenceManager::GetInstance()->getCurrentScence()->delobject(this);
			}
			else if (e->nx != 0 && nx != 0) ScenceManager::GetInstance()->getCurrentScence()->delobject(this);
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void FireShoot::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
}
