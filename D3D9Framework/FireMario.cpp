#include "FireMario.h"
#include "Game.h"


FireMario::FireMario()
{
	LoadAnimation();
	ColTag = Collision2DTag::FourSide;
	EntityTag = Tag::player;
}

void FireMario::OnKeyDown(int KeyCode)
{
	switch(KeyCode)
	{
	case DIK_A:
		if (GetTickCount() - timeAttack_Start > FIREMARIO_COOLDOWN_ATTACK)
		{
			timeAttackani_Start = GetTickCount();
			timeAttack_Start = GetTickCount();
			attackani = true;
			canattack = true;
		}
	}

	MarioModel::OnKeyDown(KeyCode);
}

void FireMario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	MarioModel::Update(dt, coObjects);

	FireMarioRunandWalkState();

	if ((GetTickCount() - timeAttackani_Start > FIREMARIO_ANI_ATTACKTIME))
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
		FireShoot* fireshoot = new FireShoot(this->Position.x, this->Position.y, direction);

		ScenceManager::GetInstance()->getCurrentScence()->AddObject(fireshoot);
	}

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
	int alpha = 255;
	if (isInvincible == true)
	{
		alpha = 144;
	}


	Vector2 camPos = camera->toCameraPosistion(this->Position.x, this->Position.y);
	int renderdirection = 1;

	std::string ani = ANI_FIRE_MARIO_IDLE;

	float crouchdiff = 0;

	if (this->state.movement == MovingStates::Walk)
	{
		ani = ANI_FIRE_MARIO_WALK;
		animation_set[ani]->setMultiplier();
	}
	else if (this->state.movement == MovingStates::Run)
	{
		ani = ANI_FIRE_MARIO_WALK;
		animation_set[ani]->setMultiplier(2);
	}

	if (!isOnGround)
	{
		ani = ANI_FIRE_MARIO_JUMP;
	}

	if (this->state.movement == MovingStates::Attack)
	{
		ani = ANI_FIRE_MARIO_ATTACK;
	}

	if (PMetter == 7)
	{
		if (state.jump == JumpingStates::Jump)
			ani = ANI_FIRE_MARIO_HIGH_JUMP;
		else if (state.movement != MovingStates::Idle)
			ani = ANI_FIRE_MARIO_HIGH_SPEED;
	}

	//when acceleration and velocity are opposite ani == crouching
	if (acc_x * vx < 0)
	{
		if (this->state.jump == JumpingStates::Stand)
		{
			//direction = -direction;
			ani = ANI_FIRE_MARIO_SKID;
		}
	}

	if (this->state.movement == MovingStates::Crouch)
	{
		crouchdiff = MARIO_FIRE_BBOX_HEIGHT - MARIO_FIRE_BBOX_HEIGHT_CROUCH;
		ani = ANI_FIRE_MARIO_CROUCH;
	}

	if (warpping != 0)
	{
		ani = ANI_FIRE_MARIO_WARP;
	}

	if (Hold != NULL)
	{
		if (this->state.movement == MovingStates::Idle)
			ani = ANI_FIRE_MARIO_HOLD_IDLE;
		if (this->state.movement == MovingStates::Walk || this->state.movement == MovingStates::Run)
			ani = ANI_FIRE_MARIO_HOLD;

		if (this->state.jump == JumpingStates::Jump)
		{
			ani = ANI_FIRE_MARIO_HOLD_JUMP;
		}
	}

	animation_set[ani]->Render(camPos.x, camPos.y + crouchdiff, this->Scale, direction, 1,alpha);

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
	AddAnimation(ANI_FIRE_MARIO_ATTACK, animation->GetAnimation(ANI_FIRE_MARIO_ATTACK));
	AddAnimation(ANI_FIRE_MARIO_WARP, animation->GetAnimation(ANI_FIRE_MARIO_WARP));

	AddAnimation(ANI_FIRE_MARIO_HOLD, animation->GetAnimation(ANI_FIRE_MARIO_HOLD));
	AddAnimation(ANI_FIRE_MARIO_HOLD_IDLE, animation->GetAnimation(ANI_FIRE_MARIO_HOLD_IDLE));
	AddAnimation(ANI_FIRE_MARIO_HOLD_JUMP, animation->GetAnimation(ANI_FIRE_MARIO_HOLD_JUMP));
}

void FireMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (this->state.movement == MovingStates::Crouch)
	{
		float crouchdiff = MARIO_FIRE_BBOX_HEIGHT - MARIO_FIRE_BBOX_HEIGHT_CROUCH;
		l = this->Position.x;
		t = this->Position.y + crouchdiff;
		r = this->Position.x + MARIO_FIRE_BBOX_WIDTH;
		b = this->Position.y + crouchdiff + MARIO_FIRE_BBOX_HEIGHT_CROUCH;
	}
	else
	{
		l = this->Position.x;
		t = this->Position.y;
		r = this->Position.x + MARIO_FIRE_BBOX_WIDTH;
		b = this->Position.y + MARIO_FIRE_BBOX_HEIGHT;
	}


}

int FireMario::getCurrentLevel()
{
	return 2;
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
			Global_Variable::GetInstance()->UpdatePmetter(PMetter);
		}
	}

	if (PMetter > 0 && (GetTickCount() - DecayPMetterTime_Start > MARIO_DECAY_PEMETTER_TIME) && state.movement != MovingStates::Run && abs(vx) < MARIO_TOP_RUNNING_SPEED)
	{
		DecayPMetterTime_Start = GetTickCount();
		PMetter--;
		Global_Variable::GetInstance()->UpdatePmetter(PMetter);
	}
}
