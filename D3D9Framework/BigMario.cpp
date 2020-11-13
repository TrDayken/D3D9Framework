#include "BigMario.h"

BigMario::BigMario()
{
	LoadAnimation();
	ColTag = Collision2DTag::FourSide;
	EntityTag = Tag::player;
}

void BigMario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	MarioModel::Update(dt, coObjects);

	BigMarioRunandWalkState();

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

void BigMario::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(this->x, this->y);

	std::string ani = ANI_BIG_MARIO_IDLE;

	float crouchdiff = 0;

	if (this->state.movement == MovingStates::Walk)
		ani = ANI_BIG_MARIO_WALK;
	else if (this->state.movement == MovingStates::Run)
		ani = ANI_BIG_MARIO_RUN;

	if (!isOnGround)
	{
			ani = ANI_BIG_MARIO_JUMP;
	}

	if (PMetter == 7 )
	{
		if (state.jump == JumpingStates::Jump)
			ani = ANI_BIG_MARIO_HIGH_JUMP;
		else if (state.movement != MovingStates::Idle)
			ani = ANI_BIG_MARIO_HIGH_SPEED;
	}
	

	//when acceleration and velocity are opposite ani == crouching
	if (acc_x * vx < 0)
	{
		if (this->state.jump == JumpingStates::Stand)
		ani = ANI_BIG_MARIO_SKID;
	}

	if (this->state.movement == MovingStates::Crouch)
	{
		crouchdiff = MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT_CROUCH;
		ani = ANI_BIG_MARIO_CROUCH;
	}


	//DebugOut(L"[INFO] Mario Pos %f %f \n", camPos.x, camPos.y);

	animation_set[ani]->Render(camPos.x, camPos.y + crouchdiff, direction, flipy);

	RenderBoundingBox(camera);
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
	AddAnimation(ANI_BIG_MARIO_CROUCH, animation->GetAnimation(ANI_BIG_MARIO_CROUCH));
	AddAnimation(ANI_BIG_MARIO_HIGH_SPEED, animation->GetAnimation(ANI_BIG_MARIO_HIGH_SPEED));
	AddAnimation(ANI_BIG_MARIO_HIGH_JUMP, animation->GetAnimation(ANI_BIG_MARIO_HIGH_JUMP));
}

void BigMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	if (this->state.movement == MovingStates::Crouch)
	{
		float crouchdiff = MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT_CROUCH;
		l = x;
		t = y + crouchdiff;
		r = x + MARIO_BIG_BBOX_WIDTH;
		b = y + crouchdiff + MARIO_BIG_BBOX_HEIGHT_CROUCH;
	}
	else
	{
		l = x;
		t = y;
		r = x + MARIO_BIG_BBOX_WIDTH;
		b = y + MARIO_BIG_BBOX_HEIGHT;
	}
}

void BigMario::BigMarioRunandWalkState()
{
	//handling mario running state
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
	//DebugOut(L"[INFO] Mario vx: %f \n", vx);
	//DebugOut(L"[INFO] PMETTER: %d \n", PMetter);

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
