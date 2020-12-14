#include "Goomba.h"

Goomba::Goomba()
{
	LoadAnimation();
	EntityTag = Tag::enemy;
	direction = 1;
	SetState(GoombaState::walking);
}

void Goomba::SetState(GoombaState state)
{
	//GameObject::SetState(state);
	switch (state)
	{
	case GoombaState::die:
		goomstate = GoombaState::die;
		DelayDeadTime_start = GetTickCount();
		vx = 0;
		ColTag = Collision2DTag::None;
		break;
	case GoombaState::walking:
		vx = -GOOMBA_WALKING_SPEED;
		goomstate = GoombaState::walking;
		break;
	case GoombaState::flydie:
		FlyDieTime_start = GetTickCount();
		DelayDeadTime_start = GetTickCount();
		ColTag = Collision2DTag::None;
		flipy = -1;
		goomstate = GoombaState::flydie;
		break;
	}
}

void Goomba::OnOverLap(GameObject* obj)
{
	//if goomba has died dont take overlapping
	if (goomstate == GoombaState::die || goomstate == GoombaState::flydie) return;

	if (obj->EntityTag == Tag::tail)
	{
		if (this->getDirection() != obj->getDirection())
			vx = -vx;
		SetState(GoombaState::flydie);
	}
}

void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->Position.x;
	top = this->Position.y;
	right = this->Position.x + GOOMBA_BBOX_WIDTH;

	if (goomstate == GoombaState::die)
		bottom = this->Position.y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = this->Position.y + GOOMBA_BBOX_HEIGHT;
}

void Goomba::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(this->Position.x, this->Position.y);
	
	float diediff = 0;

	if (goomstate == GoombaState::die)
	{
		diediff = GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE;
	}

	std::string ani = ANI_GOOMBA_WALK;

	if (goomstate == GoombaState::die) 
	{
			ani = ANI_GOOMBA_DIE;
	}

	animation_set[ani]->Render(camPos.x, camPos.y + diediff,direction, flipy);
}

void Goomba::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation(ANI_GOOMBA_IDLE, animation->GetAnimation(ANI_GOOMBA_IDLE));
	AddAnimation(ANI_GOOMBA_WALK, animation->GetAnimation(ANI_GOOMBA_WALK));
	AddAnimation(ANI_GOOMBA_DIE, animation->GetAnimation(ANI_GOOMBA_DIE));
}

void Goomba::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	std::vector<LPGAMEOBJECT> coObjectsResult;
	coEvents.clear();

	if (goomstate == GoombaState::flydie)
	{
		if (!(GetTickCount() - FlyDieTime_start > GOOMBA_TIME_FLYDIE))
			vy = -GOOMBA_FLYDIE_FORCE_VY *dt;

		vy += GOOMBA_GRAVITY * dt;
	}

	//if goomba not die -> can collison with other obj
	if (goomstate != GoombaState::die && goomstate != GoombaState::flydie)
	{
		vy += GOOMBA_GRAVITY * dt;
		//direction = right
		if (direction == 1)
			vx = GOOMBA_WALKING_SPEED * dt;
		else
			vx = -GOOMBA_WALKING_SPEED * dt;
		CalcPotentialCollisions(coObjects, coEvents);
	}

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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// pull up after collision
		this->Position.y += min_ty * dy + ny * 0.4;
		this->Position.x += min_tx * dx + nx * 0.4;


		if (ny != 0) vy = 0;
		if (nx != 0)
		{
			direction = -direction;
			//vx = -vx;
		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->EntityTag == Tag::enemy)
			{
				LPGAMEOBJECT obj = e->obj;
				obj->OnCollisionEnter(this, e->nx, e->ny);
			}
			if (e->obj->EntityTag == Tag::platform)
			{
				if (e->nx != 0)
					vx = -vx;
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

	//after die delete this
	Game* game = Game::GetInstance();
	if (goomstate == GoombaState::die|| goomstate== GoombaState::flydie)
		if (GetTickCount() -  DelayDeadTime_start >= GOOMBA_TIME_DIE)
			ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);

}

void Goomba::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
	if (goomstate == GoombaState::die) return;

	if (obj->EntityTag == Tag::shell && (obj->getVx() != 0))
	{
		if (goomstate == GoombaState::walking)
		{
			SetState(GoombaState::flydie);
		}
	}

	if (obj->EntityTag == Tag::platform)
	{
		if (nx != 0)
		{
			direction = -direction;
			vx = -vx;
		}
	}

	if (obj->EntityTag == Tag::enemy)
	{
		direction = -direction;
		vx = -vx;
	}

	if (obj->EntityTag == Tag::projectile)
	{
		SetState(GoombaState::flydie);
	}

	if (obj->EntityTag == Tag::player)
	{
		if (ny < 0)
		{
			SetState(GoombaState::die);
			vy = 0;
		}
	}
}
