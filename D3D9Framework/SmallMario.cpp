#include "SmallMario.h"

void SmallMario::SmallMarioRunandWalkState()
{
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
			{
				vx = topspeed;
				isIncreasingPMetter = true;
			}
			else
			{
				vx = -topspeed;
				isIncreasingPMetter = true;
			}
		}

	}
	else
	{
		// drag back if mario is on ground 
		if (isOnGround)
			if (vx >= MARIO_MIN_SPEED || vx <= -MARIO_MIN_SPEED)
				vx -= dt * MARIO_DRAG * vx;
			else vx = 0;
	}

	if (PMetter < MARIO_PMETTER && state.movement == MovingStates::Run && abs(vx) >= MARIO_TOP_RUNNING_SPEED && state.jump == JumpingStates::Stand)
	{
		if (isIncreasingPMetter && (GetTickCount() - IncreasePMetterTime_Start > MARIO_PLUS_PMETTER_TIME))
		{
			IncreasePMetterTime_Start = GetTickCount();
			if (PMetter == 7)
				fullMetter = true;
			else
				fullMetter = false;
			PMetter++;
		}
	}

	if (PMetter > 0 && (GetTickCount() - DecayPMetterTime_Start > MARIO_DECAY_PEMETTER_TIME) && state.movement != MovingStates::Run && abs(vx) < MARIO_TOP_RUNNING_SPEED)
	{
		DecayPMetterTime_Start = GetTickCount();
		PMetter--;
	}
}

SmallMario::SmallMario()
{
	LoadAnimation();
	ColTag = Collision2DTag::FourSide;
	EntityTag = Tag::player;
}

void SmallMario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	MarioModel::Update(dt, coObjects);

	SmallMarioRunandWalkState();

	// mario in state jump and still pressing S add up jumpheight until out of time
	if (this->state.jump == JumpingStates::Jump)
	{
		if (GetTickCount() - HighJumpTime_Start > MARIO_HIGH_JUMP_TIME)
		{
			isHighJump = false;
		}
	}

	//mario natural gravity
	vy += MARIO_GRAVITY * dt;
}

void SmallMario::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(this->x, this->y);

	std::string ani = ANI_SMALL_MARIO_IDLE;

	if (this->state.movement == MovingStates::Walk)
		ani = ANI_SMALL_MARIO_WALK;
	else if (this->state.movement == MovingStates::Run)
	{
		ani = ANI_SMALL_MARIO_RUN;
		animation_set[ani]->setMultiplier();
	}

	if (!isOnGround)
	{
		ani = ANI_SMALL_MARIO_JUMP;
	}

	if (PMetter == 7 && this->state.movement != MovingStates::Idle)
	{
		ani = ANI_SMALL_MARIO_RUN;
		this->animation_set[ani]->setMultiplier(2);
	}

	if (acc_x * vx < 0)
	{
		if (this->state.jump == JumpingStates::Stand)
		{
			ani = ANI_SMALL_MARIO_SKID;
			direction = -direction;
		}
	}

	animation_set[ani]->Render(camPos.x, camPos.y, direction);
}

void SmallMario::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation(ANI_SMALL_MARIO_IDLE, animation->GetAnimation(ANI_SMALL_MARIO_IDLE));
	AddAnimation(ANI_SMALL_MARIO_WALK, animation->GetAnimation(ANI_SMALL_MARIO_WALK));
	AddAnimation(ANI_SMALL_MARIO_SKID, animation->GetAnimation(ANI_SMALL_MARIO_SKID));
	AddAnimation(ANI_SMALL_MARIO_RUN, animation->GetAnimation(ANI_SMALL_MARIO_RUN));
	AddAnimation(ANI_SMALL_MARIO_JUMP, animation->GetAnimation(ANI_SMALL_MARIO_JUMP));
	AddAnimation(ANI_SMALL_MARIO_CROUCH, animation->GetAnimation(ANI_SMALL_MARIO_CROUCH));
}

void SmallMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARIO_SMALL_BBOX_WIDTH;
	b = y + MARIO_SMALL_BBOX_HEIGHT;
}

int SmallMario::getCurrentLevel()
{
	return 0;
}
