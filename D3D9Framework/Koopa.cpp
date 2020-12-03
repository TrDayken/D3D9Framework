#include "Koopa.h"

Koopa::Koopa()
{
	LoadAnimation();
	ColTag = Collision2DTag::FourSide;
	EntityTag = Tag::enemy;
	direction = 1;
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

void Koopa::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
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
			//vx = KOOPA_WALKING_SPEED * dt;
		if (direction == 1)
			vx = KOOPA_WALKING_SPEED * dt;
		else
			vx = -KOOPA_WALKING_SPEED * dt;
		CalcPotentialCollisions(coObjects, coEvents);
	}

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

		y += min_ty * dy + ny * 0.4;
		x += min_tx * dx + nx * 0.4;

		if (ny != 0) vy = 0;
		if (nx != 0)
		{
			//direction = -direction;
			if (koopstate != KoopaState::slide)
			{
				direction = -direction;
				//vx = -vx;
			}
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

	//DebugOut(L"[INFO] Koopa's speed: %f \n", this->vx);
}

void Koopa::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(x, y);

	std::string ani = ANI_RED_KOOPA_MOVE;

	if (koopstate == KoopaState::die)
	{
		ani = ANI_RED_KOOPA_MOVE;
	}
	
	if (koopstate == KoopaState::shell)
	{
		ani = ANI_RED_KOOPA_IDLE;
	}
	else if (koopstate == KoopaState::slide)
	{
		if (!isBeingHold)
			ani = ANI_RED_KOOPA_SLIDE;
		else
			ani = ANI_RED_KOOPA_IDLE;
	}

	animation_set[ani]->Render(camPos.x, camPos.y, -direction, flipy);
	//DebugOut(L"[INFO] KoopaState: %d \n", koopstate);

	//RenderBoundingBox(camera);
}

void Koopa::SetState(KoopaState state)
{
	//GameObject::SetState(state);
	switch (state)
	{
	case KoopaState::die:
		isHoldAble = false;
		vx = 0;
		ColTag = Collision2DTag::None;
		y += KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL - 0.4f;
		koopstate = KoopaState::die;
		break;
	case KoopaState::walking:
		isHoldAble = false;
		vx = -KOOPA_WALKING_SPEED;
		koopstate = KoopaState::walking;
		break;
	case KoopaState::shell:
		isHoldAble = true;
		vx = 0;
		koopstate = KoopaState::shell;
		break;
	case KoopaState::slide:
		isHoldAble = false;
		koopstate = KoopaState::slide;
		break;
	}
}

void Koopa::OnOverLap(GameObject* obj)
{
	if (obj->EntityTag == Tag::tail)
	{
		flipy = -1;
		SetState(KoopaState::shell);
		vy = -0.9f;
	}
}

void Koopa::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
	if (koopstate == KoopaState::die) return;

	if (obj->EntityTag == Tag::shell)
	{
		if (koopstate == KoopaState::walking)
		{
			SetState(KoopaState::die);
			vy = -0.05f;
		}
	}

	//if (obj->EntityTag == Tag::platform)
	//{
	//	if(this->koopstate != KoopaState::slide)
	//	if (nx != 0)
	//	{
	//		direction = -direction;
	//		vx = -vx;
	//	}
	//}

	if (obj->EntityTag == Tag::enemy)
	{
		direction = -direction;
		vx = -vx;
	}

	if (obj->EntityTag == Tag::projectile)
	{
		flipy = -1;
		SetState(KoopaState::die);
		vy = -0.9;
	}

	if (obj->EntityTag == Tag::player)
	{
		if (ny < 0)
		{
			if (koopstate != KoopaState::shell)
			{
				SetState(KoopaState::shell);
				vy = 0;
				EntityTag = Tag::shell;
			}
			else
			{
				SetState(KoopaState::slide);
				if (obj->getX() <= this->x)
				{
					vx = KOOPA_SLIDE_SPEED * dt;
					//obj->setVy(-10.3f);
				}
				else
				{
					vx = -KOOPA_SLIDE_SPEED * dt;
					//obj->setVy(-10.3f);
				}
			}	
		}

		if (koopstate == KoopaState::shell)
		{
			if (nx < 0)
			{	
				SetState(KoopaState::slide);
				vx = KOOPA_SLIDE_SPEED * dt;
			}
			else if (nx > 0)
			{
				SetState(KoopaState::slide);
				vx = -KOOPA_SLIDE_SPEED * dt;
			}
		}
	}
}
