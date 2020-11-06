#include "RacoonMario.h"

RacoonMario::RacoonMario()
{
	LoadAnimation();
}

void RacoonMario::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_X:
		if (canFly == true)
		{
			canFly = false;
			flying = 1;
			//lastFlying_Time = GetTickCount();
		}
	}

	MarioModel::OnKeyDown(KeyCode);
}

void RacoonMario::KeyState(BYTE* state)
{
	Game* game = Game::GetInstance();

	if (game->IsKeyDown(DIK_X))
	{
		if(!isOnGround)
		holdfly = true;
	}
	else holdfly = false;

	MarioModel::KeyState(state);
}

void RacoonMario::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_X:
		flying = 0;
	}

	MarioModel::OnKeyUp(KeyCode);
}

void RacoonMario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	MarioModel::Update(dt, coObjects);

	RacoonMarioRunandWalkState();

	// mario in state jump and still pressing S add up jumpheight until out of time
	if (this->state.jump == JumpingStates::Jump)
	{
		if (GetTickCount() - HighJumpTime_Start > MARIO_HIGH_JUMP_TIME)
		{
			isHighJump = false;
		}
	}


	if (flying == 0)
		vy += MARIO_GRAVITY * dt;

	if (flying == 1 && (GetTickCount() - Flyingtime_start) > RACCOON_MARIO_FLYTIME)
	{
		flying = 2;
		PMetter = 0;
		if (holdfly)
			vy += FLOAT_GRAVITY * dt;
		else
			vy += MARIO_GRAVITY * dt;
		
	}
	//if (flying == 1 && !(GetTickCount() - lastFlying_Time > RACCOON_MARIO_FLYTIME))
	//{
	//	flying = 2;
	//	PMetter = 0;
	//	vy += MARIO_GRAVITY * dt;
	//}

	//if (flying == 1)
	//{
	//	isOnGround = false;
	//	PMetter = 7;
	//	if (state.jump == JumpingStates::Jump)
	//	{
	//		if (holdfly && ((GetTickCount() - Pushtime) > RACCOON_MARIO_FLOATTIME))
	//		{
	//			vy = 0;
	//		}
	//		else
	//		{
	//			vy += MARIO_GRAVITY * dt;
	//		}

	//	}
	//}
	//else if (flying == 2)
	//{
	//	if (isOnGround)
	//	{
	//		flying = 0;
	//		PMetter = 0;
	//	}
	//	else
	//		PMetter = 0;
	//}

	//if (flying == 0)
	//{
	//	vy += MARIO_GRAVITY * dt;
	//}
	//vy += MARIO_GRAVITY * dt;

}

void RacoonMario::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(this->x, this->y);

	std::string ani = ANI_RACCOON_MARIO_IDLE;

	float crouchdiff = 0;

	
	if (this->state.movement == MovingStates::Walk)
		ani = ANI_RACCOON_MARIO_WALK;
	else if (this->state.movement == MovingStates::Run)
	{
		ani = ANI_RACCOON_MARIO_RUN;
		animation_set[ani]->setMultiplier();
	}

	if (!isOnGround)
	{
		ani = ANI_RACCOON_MARIO_JUMP;
	}

	if (PMetter == 7 && this->state.movement != MovingStates::Idle)
	{
		ani = ANI_RACCOON_MARIO_RUN;
		animation_set[ani]->setMultiplier(2);
	}

	//when acceleration and velocity are opposite ani == crouching
	if (acc_x * vx < 0)
	{
		if (this->state.jump == JumpingStates::Stand)
			ani = ANI_RACCOON_MARIO_SKID;
	}

	if (this->state.movement == MovingStates::Crouch)
	{
		crouchdiff = MARIO_RACCOON_BBOX_HEIGHT - MARIO_RACCOON_BBOX_HEIGHT_CROUCH;
		ani = ANI_RACCOON_MARIO_CROUCH;
	}

	animation_set[ani]->Render(camPos.x, camPos.y + crouchdiff, direction);

}

void RacoonMario::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation(ANI_RACCOON_MARIO_IDLE, animation->GetAnimation(ANI_RACCOON_MARIO_IDLE));
	AddAnimation(ANI_RACCOON_MARIO_WALK, animation->GetAnimation(ANI_RACCOON_MARIO_WALK));
	AddAnimation(ANI_RACCOON_MARIO_SKID, animation->GetAnimation(ANI_RACCOON_MARIO_SKID));
	AddAnimation(ANI_RACCOON_MARIO_RUN, animation->GetAnimation(ANI_RACCOON_MARIO_RUN));
	AddAnimation(ANI_RACCOON_MARIO_JUMP, animation->GetAnimation(ANI_RACCOON_MARIO_JUMP));
	AddAnimation(ANI_RACCOON_MARIO_CROUCH, animation->GetAnimation(ANI_RACCOON_MARIO_CROUCH));

	AddAnimation(ANI_RACCOON_MARIO_FLOAT, animation->GetAnimation(ANI_RACCOON_MARIO_FLOAT));
	AddAnimation(ANI_RACCOON_MARIO_FLY, animation->GetAnimation(ANI_RACCOON_MARIO_FLY));
	AddAnimation(ANI_RACCOON_MARIO_SPIN, animation->GetAnimation(ANI_RACCOON_MARIO_SPIN));
	AddAnimation(ANI_RACCOON_MARIO_HOLD_IDLE, animation->GetAnimation(ANI_RACCOON_MARIO_HOLD_IDLE));
	AddAnimation(ANI_RACCOON_MARIO_HOLD_MOVE, animation->GetAnimation(ANI_RACCOON_MARIO_HOLD_MOVE));
	AddAnimation(ANI_RACCOON_MARIO_KICK, animation->GetAnimation(ANI_RACCOON_MARIO_KICK));
}

void RacoonMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (this->state.movement == MovingStates::Crouch)
	{
		float crouchdiff = MARIO_RACCOON_BBOX_HEIGHT - MARIO_RACCOON_BBOX_HEIGHT_CROUCH;
		l = x;
		t = y + crouchdiff;
		r = x + MARIO_RACCOON_BBOX_WIDTH;
		b = y + crouchdiff + MARIO_RACCOON_BBOX_HEIGHT_CROUCH;
	}
	else
	{
		l = x;
		t = y;
		r = x + MARIO_RACCOON_BBOX_WIDTH;
		b = y + MARIO_RACCOON_BBOX_HEIGHT;
	}
}

void RacoonMario::RacoonMarioRunandWalkState()
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
			PMetter++;
		}

		if (PMetter == 7)
		{
			fullMetter = true;
			canFly = true;
		}
		else
		{
			fullMetter = false;
			canFly = false;
		}
	}

	if (PMetter > 0 && (GetTickCount() - DecayPMetterTime_Start > MARIO_DECAY_PEMETTER_TIME) && state.movement != MovingStates::Run && abs(vx) < MARIO_TOP_RUNNING_SPEED)
	{
		DecayPMetterTime_Start = GetTickCount();
		PMetter--;
	}
}
