#include "FireMario.h"



FireMario::FireMario()
{
	LoadAnimation();

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
		FireShoot* fireshoot = new FireShoot(x, y, direction);

		ScenceManager::GetInstance()->getCurrentScence()->addobject(fireshoot);
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
	Vector2 camPos = camera->toCameraPosistion(this->x, this->y);

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

	if (this->state.movement == MovingStates::Attack)
	{
		ani = ANI_FIRE_MARIO_ATTACK;
	}


	if (!isOnGround)
	{
		ani = ANI_FIRE_MARIO_JUMP;
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
	AddAnimation(ANI_FIRE_MARIO_ATTACK, animation->GetAnimation(ANI_FIRE_MARIO_ATTACK));
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

	DebugOut(L"[INFO] Mario vx: %f \n", vx);
	DebugOut(L"[INFO] PMETTER: %d \n", PMetter);

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
