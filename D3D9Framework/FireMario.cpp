#include "FireMario.h"



FireMario::FireMario()
{
	LoadAnimation();
}

void FireMario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	MarioModel::Update(dt, coObjects);

	FireMarioRunandWalkState();

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

void FireMario::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(this->x, this->y);

	std::string ani = ANI_FIRE_MARIO_IDLE;

	float crouchdiff = 0;

	if (this->state.movement == MovingStates::Walk)
		ani = ANI_FIRE_MARIO_WALK;
	else if (this->state.movement == MovingStates::Run)
		ani = ANI_FIRE_MARIO_RUN;

	if (!isOnGround)
	{
		ani = ANI_FIRE_MARIO_JUMP;
	}

	if (PMetter == 7 && this->state.movement != MovingStates::Idle)
	{
		ani = ANI_FIRE_MARIO_HIGH_SPEED;
	}

	//when acceleration and velocity are opposite ani == crouching
	if (acc_x * vx < 0)
	{
		if (this->state.jump == JumpingStates::Stand)
			ani = ANI_FIRE_MARIO_SKID;
	}

	if (this->state.movement == MovingStates::Crouch)
	{
		crouchdiff = MARIO_FIRE_BBOX_HEIGHT - MARIO_FIRE_BBOX_HEIGHT_CROUCH;
		ani = ANI_FIRE_MARIO_CROUCH;
	}

	animation_set[ani]->Render(camPos.x, camPos.y + crouchdiff, direction);

	//RenderBoundingBox(camera);
	//DebugOut(L"[INFO] %f, %f \n", camPos.x, camPos.y)
}

void FireMario::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation(ANI_FIRE_MARIO_IDLE, animation->GetAnimation(ANI_FIRE_MARIO_IDLE));
	AddAnimation(ANI_FIRE_MARIO_WALK, animation->GetAnimation(ANI_FIRE_MARIO_WALK));
	AddAnimation(ANI_FIRE_MARIO_SKID, animation->GetAnimation(ANI_FIRE_MARIO_SKID));
	AddAnimation(ANI_FIRE_MARIO_RUN, animation->GetAnimation(ANI_FIRE_MARIO_RUN));
	AddAnimation(ANI_FIRE_MARIO_JUMP, animation->GetAnimation(ANI_FIRE_MARIO_JUMP));
	AddAnimation(ANI_FIRE_MARIO_CROUCH, animation->GetAnimation(ANI_FIRE_MARIO_CROUCH));
	AddAnimation(ANI_FIRE_MARIO_HIGH_SPEED, animation->GetAnimation(ANI_FIRE_MARIO_HIGH_SPEED));
	AddAnimation(ANI_FIRE_MARIO_HIGH_JUMP, animation->GetAnimation(ANI_FIRE_MARIO_HIGH_JUMP));
}

void FireMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (this->state.movement == MovingStates::Crouch)
	{
		float crouchdiff = MARIO_FIRE_BBOX_HEIGHT - MARIO_FIRE_BBOX_HEIGHT_CROUCH;
		l = x;
		t = y + crouchdiff;
		r = x + MARIO_FIRE_BBOX_WIDTH;
		b = y + crouchdiff + MARIO_FIRE_BBOX_HEIGHT_CROUCH;
	}
	else
	{
		l = x;
		t = y;
		r = x + MARIO_FIRE_BBOX_WIDTH;
		b = y + MARIO_FIRE_BBOX_HEIGHT;
	}


}

void FireMario::FireMarioRunandWalkState()
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
				vx = topspeed;
			else
				vx = -topspeed;
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
}
