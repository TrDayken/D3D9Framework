#include "Goomba.h"

Goomba::Goomba()
{
	LoadAnimation();
	Objecttag = Tag::enemy;
	flydie = false;
	timedie = 0;
}

void Goomba::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		vx = 0;
		//collision = CCollision::None;
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

		Vector2 pScale(1, 1);
	string ani = ANI_GOOMBA_WALK;

	if (state == GOOMBA_STATE_DIE) {
		if (!flydie)
			ani = ANI_GOOMBA_DIE;
		else
		{
			ani = ANI_GOOMBA_IDLE;
			pScale.y = -pScale.y;
		}
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
	vy += GOOMBA_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	if (!flydie)
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
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		y += min_ty * dy + ny * 0.4;
		x += min_tx * dx + nx * 0.4;
		//y += min_ty * dy + ny * 0.5;
		if (ny != 0) vy = 0;
		if (nx != 0)
		{
			vx = -vx;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	Game* game = Game::GetInstance();
	if (state == GOOMBA_STATE_DIE && !flydie)
		if (timedie >= GOOMA_TIME_DIE)
			ScenceManager::GetInstance()->getCurrentScence()->delobject(this);
		else
		{
			timedie += dt;
			vy = 0;
		}

	float camy = ScenceManager::GetInstance()->getCurrentScence()->getCamera()->getCameraPositionY();

	if (y > camy + WINDOW_HEIGHT) ScenceManager::GetInstance()->getCurrentScence()->delobject(this);
}

void Goomba::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
	if (obj->Objecttag == Tag::enemy) return;
	if (obj->Objecttag == Tag::player)
	{
		if (ny < 0)
		{
			SetState(GOOMBA_STATE_DIE);
			vy = 0;
		}
		//else
			//obj->DownLevel();
	}
	else if (obj->Objecttag != Tag::player)
	{
		flydie = TRUE;
		vy = -GOOMBA_FLY_DIE;
		SetState(GOOMBA_STATE_DIE);
	}
}
