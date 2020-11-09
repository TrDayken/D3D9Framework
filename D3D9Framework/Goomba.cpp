#include "Goomba.h"

Goomba::Goomba()
{
	LoadAnimation();
	EntityTag = Tag::enemy;
}

void Goomba::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		DelayDeadTime_start = GetTickCount();
		vx = 0;
		ColTag = Collision2DTag::None;
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE - 0.4;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
}

void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void Goomba::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(x, y);
	
	string ani = ANI_GOOMBA_WALK;

	if (state == GOOMBA_STATE_DIE) 
	{
			ani = ANI_GOOMBA_DIE;
	}

	animation_set[ani]->Render(camPos.x, camPos.y,direction);
}

void Goomba::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation(ANI_GOOMBA_IDLE, animation->GetAnimation(ANI_GOOMBA_IDLE));
	AddAnimation(ANI_GOOMBA_WALK, animation->GetAnimation(ANI_GOOMBA_WALK));
	AddAnimation(ANI_GOOMBA_DIE, animation->GetAnimation(ANI_GOOMBA_DIE));
}

void Goomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);


	

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	std::vector<LPGAMEOBJECT> coObjectsResult;
	coEvents.clear();

	if (state != GOOMBA_STATE_DIE)
	{
		vy += GOOMBA_GRAVITY * dt;
		vx = GOOMBA_WALKING_SPEED * dt;
		CalcPotentialCollisions(coObjects, coEvents);
	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//filter colision axis by axis
		if (min_tx > min_ty)
		{
			float px = x;
			x += min_ty * dx;
			y += min_ty * dy + ny * 0.4f;
			dy = 0;

			//DebugOut(L"		[X]point = : %f \n",px);
			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if (coEvents.size() > 0)
			{
				FilterCollisionX(coEvents, coEventsResult, min_tx, nx, rdx);
				//x -= min_ty * dx;
				x += min_tx * dx + nx * 0.4f;
				DebugOut(L"		[X] coEvents.size() = : %d \n", coEvents.size());
			}
			else
			{
				x = px + dx;
				nx = 0;
			}
			dy = vy * dt;

		}
		else
		{
			float py = y;
			x += min_tx * dx + nx * 0.4f;
			y += min_tx * dy;
			dx = 0;
			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if (coEvents.size() > 0)
			{
				FilterCollisionY(coEvents, coEventsResult, min_ty, ny, rdy);
				y += min_ty * dy + ny * 0.4f;
			}

			else
			{
				y = py + dy;
				ny = 0;
			}
			dx = vx * dt;
		}

		//if (coEvents.size() == 0)
		//{
		//	x += dx;
		//	y += dy;
		//}
		//else
		//{
		//	float min_tx, min_ty, nx = 0, ny = 0;
		//	float rdx = 0;
		//	float rdy = 0;
		//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//	y += min_ty * dy + ny * 0.4;
		//	x += min_tx * dx + nx * 0.4;

		//	if (ny != 0) vy = 0;
		//	if (nx != 0)
		//	{
		//		vx = -vx;
		//	}
		//}
		if (ny != 0) vy = 0;
		if (nx != 0)
		{
			vx = -vx;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


		//after die delete this
		Game* game = Game::GetInstance();
		if (state == GOOMBA_STATE_DIE )
			if (GetTickCount() -  DelayDeadTime_start >= GOOMA_TIME_DIE)
				ScenceManager::GetInstance()->getCurrentScence()->delobject(this);

		float camy = ScenceManager::GetInstance()->getCurrentScence()->getCamera()->getCameraPositionY();

		if (y > camy + WINDOW_HEIGHT) ScenceManager::GetInstance()->getCurrentScence()->delobject(this);
	}
}

void Goomba::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
	if (obj->EntityTag == Tag::enemy) return;

	if (obj->EntityTag == Tag::projectile)
	{
		SetState(GOOMBA_STATE_DIE);
		vy = vx = 0;
	}

	if (obj->EntityTag == Tag::player)
	{
		if (ny < 0)
		{
			SetState(GOOMBA_STATE_DIE);
			vy = 0;
		}
		//else
			//obj->DownLevel();
	}
	else if (obj->EntityTag != Tag::player)
	{
		SetState(GOOMBA_STATE_DIE);
	}
}
