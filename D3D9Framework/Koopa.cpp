#include "Koopa.h"

Koopa::Koopa()
{
	LoadAnimation();
	ColTag = Collision2DTag::FourSide;
	EntityTag = Tag::enemy;
	direction = -1;
	koopstate = KoopaState::walking;
}

void Koopa::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation(ANI_RED_KOOPA_MOVE, animation->GetAnimation(ANI_RED_KOOPA_MOVE));
	AddAnimation(ANI_RED_KOOPA_IDLE, animation->GetAnimation(ANI_RED_KOOPA_IDLE));

	AddAnimation(ANI_RED_KOOPA_SLIDE, animation->GetAnimation(ANI_RED_KOOPA_SLIDE));
	AddAnimation(ANI_RED_KOOPA_CROUCH, animation->GetAnimation(ANI_RED_KOOPA_CROUCH));
}

void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x; 
	top = y;
	right = x + KOOPA_BBOX_WIDTH;
	if (koopstate == KoopaState::shell || koopstate == KoopaState::slide)
		bottom = y + KOOPA_BBOX_HEIGHT_SHELL;
	else
		bottom = y + KOOPA_BBOX_HEIGHT;
}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	vy += KOOPA_GRAVITY * dt;


	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	std::vector<LPGAMEOBJECT> coObjectsResult;
	coEvents.clear();

	if (koopstate != KoopaState::die)
	{
		if(koopstate != KoopaState::shell && koopstate != KoopaState::slide)
			vx = KOOPA_WALKING_SPEED * dt;
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

			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if (coEvents.size() > 0)
			{
				FilterCollisionX(coEvents, coEventsResult, min_tx, nx, rdx);
				x += min_tx * dx + nx * 0.4f;
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

		if (ny != 0) vy = 0;
		if (nx != 0)
		{
			direction = -direction;
			vx = -vx;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void Koopa::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(x, y);

	string ani = ANI_RED_KOOPA_MOVE;

	if (koopstate == KoopaState::die)
	{
		ani = ANI_RED_KOOPA_MOVE;
	}
	
	if (koopstate == KoopaState::shell)
	{
		ani = ANI_RED_KOOPA_IDLE;
	}
	else if (koopstate == KoopaState::slide)
		ani = ANI_RED_KOOPA_SLIDE;

	animation_set[ani]->Render(camPos.x, camPos.y, direction);
	DebugOut(L"%d \n", koopstate);

	//RenderBoundingBox(camera);
}

void Koopa::SetState(KoopaState state)
{
	//GameObject::SetState(state);
	switch (state)
	{
	case KoopaState::die:
		vx = 0;
		ColTag = Collision2DTag::None;
		y += KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL - 0.4;
		koopstate = KoopaState::die;
		break;
	case KoopaState::walking:
		vx = -KOOPA_WALKING_SPEED;
		koopstate = KoopaState::walking;
		break;
	case KoopaState::shell:
		koopstate = KoopaState::shell;
		vx = 0;
		break;
	case KoopaState::slide:
		koopstate = KoopaState::slide;
	}
}

void Koopa::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
	if (obj->EntityTag == Tag::enemy) return;

	if (obj->EntityTag == Tag::projectile)
	{
		SetState(KoopaState::die);
		vx = 0, vy = 0;
	}

	if (obj->EntityTag == Tag::player)
	{
		if (ny < 0)
		{
			if (koopstate != KoopaState::shell)
			{
				SetState(KoopaState::shell);
				vy = 0;
			}
			else
			{
				SetState(KoopaState::slide);
				if (obj->getDirection() == 1)
				{
					vx += KOOPA_SLIDE_SPEED * dt;
					//obj->setVy(-0.3f);
				}
				else
				{
					vx -= KOOPA_SLIDE_SPEED * dt;
					//obj->setVy(-0.3f);
				}
			}
		}
	}
}
