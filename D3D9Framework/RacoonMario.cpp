#include "RacoonMario.h"
#include "Game.h"

RacoonMario::RacoonMario()
{
	LoadAnimation();
	ColTag = Collision2DTag::FourSide;
	EntityTag = Tag::player;
}

void RacoonMario::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_X:
		if (canFly == true)
		{
			setJumpstate(JumpingStates::Fly);
			//isOnGround = false;
			canFly = false;
			isFlying = true;
			Flyingtime_start = GetTickCount();
			vy = -MARIO_GRAVITY * dt;
			//lastFlying_Time = GetTickCount();
		}
		//else if (isOnGround) 
		//	vy = -FLOAT_GRAVITY * dt;
		break;
	case DIK_A:
		if (GetTickCount() - timeAttack_Start > RACOON_ATTACK_COOLDOWN)
		{
			timeAttackani_Start = GetTickCount();
			timeAttack_Start = GetTickCount();
			attackani = true;
			canattack = true;
		}
		break;
	}

	MarioModel::OnKeyDown(KeyCode);
}

void RacoonMario::KeyState(BYTE* state)
{
	Game* game = Game::GetInstance();

	if (game->IsKeyDown(DIK_X))
	{
		if(!isOnGround)
		holdFloat = true;
	}
	else holdFloat = false;

	MarioModel::KeyState(state);
}

void RacoonMario::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_X:
		isFlying = false;
		isFloating = false;
		break;
	}

	MarioModel::OnKeyUp(KeyCode);
}

void RacoonMario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	MarioModel::Update(dt, coObjects);

	RacoonMarioRunandWalkState();

	if ((GetTickCount() - timeAttackani_Start > RACOON_ATTACK_ANI_TIME))
	{
		attackani = false;
	}

	if (attackani)
	{
		setMovestate(MovingStates::Attack);
	}

	if (canattack)
	{
		canattack = false;
		AttackTail* tail;
		if (direction == 1)
		{
			tail = new AttackTail(this->Position.x + 25, this->Position.y + 45, direction);
			tail->setDirection(direction);
		}
		else
		{
			tail = new AttackTail(this->Position.x - 30, this->Position.y + 45, direction);
			tail->setDirection(direction);
		}

		ScenceManager::GetInstance()->getCurrentScence()->AddObject(tail);
	}

	// mario in state jump and still pressing S add up jumpheight until out of time
	if (this->state.jump == JumpingStates::Jump)
	{
		if (GetTickCount() - HighJumpTime_Start > MARIO_HIGH_JUMP_TIME)
		{
			isHighJump = false;
		}
	}


	if (Game::GetInstance()->IsKeyDown(DIK_Z))
	{
		readytoAttack = false;
		state.movement = MovingStates::Attack;
	}


	//mario fly logic
	if (state.jump == JumpingStates::Fly && !isOnGround)
	{

		if (!(GetTickCount() - Flyingtime_start > RACCOON_MARIO_FLYTIME) && isFlying)
		{
			PMetter = 0;
			Global_Variable::GetInstance()->UpdatePmetter(PMetter);
			vy = -RACCOON_MARIO_FLY_FROCE * dt;
		}
		else
		{
			state.jump = JumpingStates::Float;
		}
	}
	else if (holdFloat)
	{
		if (state.jump == JumpingStates::Float && !isOnGround);
		{
			vy = RACCOON_MARIO_FLOAT_FROCE * dt;
		}
	}
	else vy += MARIO_GRAVITY * dt;
	
	//if (flying == 0 && !isOnGround)
	//	if (holdfly)
	//	{
	//		vy = FLOAT_GRAVITY;
	//		setJumpstate(JumpingStates::Float);
	//	}
	//	else
	//	{
	//		vy += MARIO_GRAVITY * dt;
	//	}
	//
	//DebugOut(L"%d \n", flying);
	//if (flying == 1 && (GetTickCount() - Flyingtime_start) < RACCOON_MARIO_FLYTIME)
	//{
	//	flying = 2;
	//	PMetter = 0;
	//	if (holdfly)
	//	{
	//		vy = -FLOAT_GRAVITY * dt;
	//		//setJumpstate(JumpingStates::Fly);
	//	}
	//	else
	//	{
	//		vy = -RACCOON_MARIO_FLY_FROCE * dt;
	//		setJumpstate(JumpingStates::Fly);
	//	}
	//	
	//}
	//else if(flying ==2 && !(GetTickCount() - Flyingtime_start < RACCOON_MARIO_FLYTIME))
	//	flying = 0;
}

void RacoonMario::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(this->Position.x, this->Position.y);

	std::string ani = ANI_RACCOON_MARIO_IDLE;

	float crouchdiff = 0;

	
	if (this->state.movement == MovingStates::Walk)
		ani = ANI_RACCOON_MARIO_WALK;
	else if (this->state.movement == MovingStates::Run)
	{
		ani = ANI_RACCOON_MARIO_RUN;
		animation_set[ani]->setMultiplier();
	}

	if (state.movement == MovingStates::Attack)
	{
		ani = ANI_RACCOON_MARIO_SPIN;
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
		{
			ani = ANI_RACCOON_MARIO_SKID;
			direction = -direction;
		}
	}

	if (this->state.movement == MovingStates::Crouch)
	{
		crouchdiff = MARIO_RACCOON_BBOX_HEIGHT - MARIO_RACCOON_BBOX_HEIGHT_CROUCH;
		ani = ANI_RACCOON_MARIO_CROUCH;
	}

	if (!isOnGround)
	{
		if (state.jump == JumpingStates::Fly)
			ani = ANI_RACCOON_MARIO_FLY;
		else if (state.jump == JumpingStates::Float)
			ani = ANI_RACCOON_MARIO_FLOAT;
		else
			ani = ANI_RACCOON_MARIO_JUMP;

		crouchdiff = 0;
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
		l = this->Position.x;
		t = this->Position.y + crouchdiff;
		r = this->Position.x + MARIO_RACCOON_BBOX_WIDTH;
		b = this->Position.y + crouchdiff + MARIO_RACCOON_BBOX_HEIGHT_CROUCH;
	}
	else
	{
		l = this->Position.x;
		t = this->Position.y;
		r = this->Position.x + MARIO_RACCOON_BBOX_WIDTH;
		b = this->Position.y + MARIO_RACCOON_BBOX_HEIGHT;
	}
}

int RacoonMario::getCurrentLevel()
{
	return 3;
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
			Global_Variable::GetInstance()->UpdatePmetter(PMetter);
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
		Global_Variable::GetInstance()->UpdatePmetter(PMetter);
	}

	DebugOut(L"[INFO] PMETTER: %d \n ", PMetter);
}
