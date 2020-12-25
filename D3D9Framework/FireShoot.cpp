#include "FireShoot.h"


FireShoot::FireShoot(float x, float y, int direction)
{
	EntityTag = Tag::projectile;
	this->Position.x = x;
	this->Position.y = y;
	vx = direction * BULLET_VX;

	this->ColTag = Collision2DTag::None; 
	LoadAnimation();
}

FireShoot::~FireShoot()
{
}

void FireShoot::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(this->Position.x, this->Position.y);

	std::string ani = ANI_BULLET;

	animation_set[ani]->Render(camPos.x, camPos.y, direction);
}

void FireShoot::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + BULLET_BBOX_WIDTH;
	b = this->Position.y + BULLET_BBOX_HEIGHT;
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

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		this->Position.x += dx;
		this->Position.y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		this->Position.x += min_tx * dx + nx * 0.4;
		this->Position.y += min_ty * dy + ny * 0.4;
		if (ny < 0) vy = -BULLET_BOUNCE;


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->EntityTag == Tag::enemy)
			{
				LPGAMEOBJECT obj = e->obj;
				obj->OnCollisionEnter(this, e->nx, e->ny);
				ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
			}

			//delete when have horizontal collision with another object
			else if (e->nx != 0 && nx != 0) 
				ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
	
