#include "GreenKoopa.h"

GreenKoopa::GreenKoopa()
{
	LoadAnimation();
	ColTag = Collision2DTag::FourSide;
	EntityTag = Tag::enemy;
	direction = -1;
	koopstate = KoopaState::fly;

	this->setRenderOrder(2);
}

void GreenKoopa::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation(ANI_RED_KOOPA_MOVE, animation->GetAnimation(ANI_RED_KOOPA_MOVE));
	AddAnimation(ANI_RED_KOOPA_IDLE, animation->GetAnimation(ANI_RED_KOOPA_IDLE));
	AddAnimation(ANI_RED_KOOPA_SLIDE, animation->GetAnimation(ANI_RED_KOOPA_SLIDE));
	AddAnimation(ANI_RED_KOOPA_CROUCH, animation->GetAnimation(ANI_RED_KOOPA_CROUCH));
}

void GreenKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isBeingHold) return;

	left = this->Position.x;
	top = this->Position.y;
	right = this->Position.x + KOOPA_BBOX_WIDTH;
	if (koopstate == KoopaState::shell || koopstate == KoopaState::slide)
		bottom = this->Position.y + KOOPA_BBOX_HEIGHT_SHELL;
	else
		bottom = this->Position.y + KOOPA_BBOX_HEIGHT;
}

void GreenKoopa::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (isBeingHold) return;

	GameObject::Update(dt);

	vy += KOOPA_GRAVITY * dt;

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	std::vector<LPGAMEOBJECT> coObjectsResult;
	coEvents.clear();

	if (koopstate != KoopaState::die)
	{
		if (koopstate != KoopaState::shell && koopstate != KoopaState::slide)
		{
			this->UpdatePosition();
			if (direction == 1)
				vx = KOOPA_WALKING_SPEED * dt;
			else
				vx = -KOOPA_WALKING_SPEED * dt;
		}
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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		this->Position.y += min_ty * dy + ny * 0.4;
		this->Position.x += min_tx * dx + nx * 0.4;

		if (ny != 0)
		{
			vy = 0;
			if (ny < 0)
			{
				if (koopstate == KoopaState::fly)
				{
					vy -= 0.9;
				}
			}
		}
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
				direction = -direction;
			}

			if ((e->obj->EntityTag == Tag::platform) && (this->koopstate != KoopaState::shell) || (this->koopstate != KoopaState::slide))
			{
				if (e->ny < 0)
				{
					maxleft = e->obj->getX();
					maxright = e->obj->getX() + e->obj->getWidth() - KOOPA_BBOX_WIDTH;
				}

				if (e->nx != 0)
					vx = -vx;
			}

			if (e->obj->EntityTag == Tag::platform && this->koopstate == KoopaState::slide)
			{
				if (e->nx != 0)
				{
					vx = -vx;
				}
			}

			if ((e->obj->EntityTag == Tag::questionblock) && this->koopstate == KoopaState::slide)
			{
				if (e->nx != 0)
				{
					e->obj->OnCollisionEnter(this, e->nx, e->ny);
					direction = -direction;
				}
			}

			if ((e->obj->EntityTag == Tag::brick) && this->koopstate == KoopaState::slide);
			{
				if (e->nx != 0)
				{
					e->obj->OnCollisionEnter(this, e->nx, e->ny);
					direction = -direction;
					vx = -vx;
				}

			}


		}



		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void GreenKoopa::Render(Camera* camera)
{
	RenderBoundingBox(camera);

	Vector2 camPos = camera->toCameraPosistion(this->Position.x, this->Position.y);

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

	animation_set[ani]->Render(camPos.x, camPos.y, this->Scale, -direction, flipy);
	//DebugOut(L"[INFO] KoopaState: %d \n", koopstate);

	//RenderBoundingBox(camera);
}

void GreenKoopa::setIsBeingHold(bool isBeingHold)
{
	GameObject::setIsBeingHold(isBeingHold);

	this->koopstate = KoopaState::slide;
}

void GreenKoopa::SetState(KoopaState state)
{
	//GameObject::SetState(state);
	switch (state)
	{
	case KoopaState::die:
		isHoldAble = false;
		vx = 0;
		ColTag = Collision2DTag::None;
		this->Position.y += KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL - 0.4f;
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

void GreenKoopa::OnOverLap(GameObject* obj)
{
	if (obj->EntityTag == Tag::tail)
	{
		flipy = -1;
		SetState(KoopaState::shell);
		vy = -0.9f;
	}
}

void GreenKoopa::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
	if (koopstate == KoopaState::die) return;

	if (obj->EntityTag == Tag::shell)
	{
		if (koopstate == KoopaState::walking)
		{
			SetState(KoopaState::die);
			vy = -0.9;
		}

		if (koopstate == KoopaState::shell)
		{
			SetState(KoopaState::slide);
			this->vx = -obj->getVx();
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

			if (koopstate != KoopaState::shell && koopstate != KoopaState::fly)
			{
				SetState(KoopaState::shell);
				vy = 0;
				EntityTag = Tag::shell;
			}
			else
			{
				if (koopstate != KoopaState::fly)
				{
					SetState(KoopaState::slide);
					if (obj->getX() <= this->Position.x)
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

			if (koopstate == KoopaState::fly)
			{
				SetState(KoopaState::walking);
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

void GreenKoopa::UpdatePosition()
{
	//if (this->Position.x < maxleft)
	//{
	//	direction = 1;
	//	vx = KOOPA_WALKING_SPEED;
	//}
	//else if (this->Position.x > maxright)
	//{
	//	direction = -1;
	//	vx = -KOOPA_WALKING_SPEED;
	//}
}

void GreenKoopa::setVx(float vx)
{
	this->vx = 0;

	this->vx = vx;
}

void GreenKoopa::flying()
{
}
