#include "BigMario.h"

BigMario::BigMario()
{
	LoadAnimation();
}

void BigMario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	MarioModel::Update(dt, coObjects);

	float topspeed = 0;

	if (this->state.movement == MovingStates::Walk || this->state.movement == MovingStates::Run)
	{
		if (this->state.movement == MovingStates::Walk)
		{
			topspeed = MARIO_TOP_WALKING_SPEED;
		}
		else if (this->state.movement == MovingStates::Run)
		{
			topspeed = MARIO_TOP_RUNNING_SPEED;
		}


		if (acc_x != 0)
		{
			if (abs(vx + dt * acc_x) < topspeed)
			{
				vx += dt * acc_x;
			}
			else if (acc_x > 0)
				vx = topspeed;
			else
				vx = -topspeed;
		}
	}
	else
	{
		if (vx >= MARIO_MIN_SPEED || vx <= -MARIO_MIN_SPEED)
			vx -= dt * MARIO_DRAG * vx;
		else vx = 0;
	}

	vy += MARIO_GRAVITY * dt;
	
	
}

void BigMario::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(this->x, this->y);

	std::string ani = ANI_BIG_MARIO_IDLE;

	if (this->state.movement == MovingStates::Walk)
		ani = ANI_BIG_MARIO_WALK;
	else if (this->state.movement == MovingStates::Run)
		ani = ANI_BIG_MARIO_RUN;

	animation_set[ani]->Render(camPos.x, camPos.y);

	//DebugOut(L"[INFO] %f, %f \n", camPos.x, camPos.y);
}

void BigMario::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation(ANI_BIG_MARIO_IDLE, animation->GetAnimation(ANI_BIG_MARIO_IDLE));
	AddAnimation(ANI_BIG_MARIO_WALK, animation->GetAnimation(ANI_BIG_MARIO_WALK));
	AddAnimation(ANI_BIG_MARIO_SKID, animation->GetAnimation(ANI_BIG_MARIO_SKID));
	AddAnimation(ANI_BIG_MARIO_RUN, animation->GetAnimation(ANI_BIG_MARIO_RUN));
	AddAnimation(ANI_BIG_MARIO_JUMP, animation->GetAnimation(ANI_BIG_MARIO_JUMP));
}

void BigMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x; 
	t = y;
	r = x + MARIO_BIG_BBOX_WIDTH;
	b = y + MARIO_BIG_BBOX_HEIGHT;
}

void BigMario::BigMarioRunandWalkState()
{
}
