#include "MarioModel.h"
#include "SmokeFx.h"

#include "FXObjectManager.h"

MarioModel::MarioModel(float x, float y)
{
	start_x = x; 
	start_y = y;
	this->Position.x = x; 
	this->Position.y = y;

	this->changestate = -1;

	InvincibleFrame = 0;

	LoadAnimation();

	state.movement = MovingStates::Idle;
}

void MarioModel::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	
	GameObject::Update(dt);

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	std::vector<LPGAMEOBJECT> coObjectsResult;
	coEvents.clear();

	

	//if (x + dx <= 1)
	//{
	//	dx = 0;
	//	x = 2;
	//	//DebugOut(L"[INFO] mario position %d, \n", x);
	//}

	// turn off collision when die 
	if (state.movement != MovingStates::Die)
	{
		CalcPotentialCollisions(coObjects, coEvents);
		for (UINT i = 0; i < coEvents.size(); i++)  coObjectsResult.push_back(coEvents[i]->obj);
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - InvincibleTime_Start > MARIO_UNTOUCHABLE_TIME)
	{
		InvincibleTime_Start = 0;
		InvincibleFrame = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		this->Position.x += dx;
		this->Position.y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//filter colision axis by axis
		if (min_tx > min_ty)
		{
			this->Position.x += min_ty * dx;
			this->Position.y += min_ty * dy + ny * 0.4f;
			dy = 0;

			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if (coEvents.size() > 0)
			{
				FilterCollisionX(coEvents, coEventsResult, min_tx, nx, rdx);
				//x -= min_ty * dx;
				this->Position.x += min_tx * dx + nx * 0.4f - min_ty * dx;
			}
			else
			{
				this->Position.x += dx - min_ty * dx;
				nx = 0;
			}
			dy = vy * dt;

		}
		else
		{
			//float py = y;
			this->Position.x += min_tx * dx + nx * 0.4f;
			this->Position.y += min_tx * dy;
			dx = 0;
			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if (coEvents.size() > 0)
			{
				FilterCollisionY(coEvents, coEventsResult, min_ty, ny, rdy);
				this->Position.y += min_ty * dy + ny * 0.4f - min_tx * dy;
			}

			else
			{
				this->Position.y = this->Position.y + dy - min_tx * dy;
				ny = 0;
			}
			dx = vx * dt;
		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			//if collide with obj with the right tag -> process the mario collide with the object
			if (e->obj->EntityTag == Tag::shell && e->obj->IsHoldAble() && Game::GetInstance()->IsKeyDown(DIK_A))
			{
				e->obj->setIsBeingHold(true);
				e->obj->setIsHoldAble(false);
				Hold = e->obj;
			}
			else if (e->obj->EntityTag == Tag::enemy || e->obj->EntityTag == Tag::shell)
			{
				LPGAMEOBJECT obj = e->obj;
				obj->OnCollisionEnter(this, e->nx, e->ny);
				if (e->ny < 0)
				{
					vy = -MARIO_DEFLECT_MOB * dt;
					state.jump = JumpingStates::Jump;
				}
				else
				{
					//mario take damage
				}
					
			}
			else if (e->obj->EntityTag == Tag::questionblock)
			{
				LPGAMEOBJECT obj = e->obj;
				if (e->ny > 0)
					obj->OnCollisionEnter(this, e->nx, e->ny);
			}

		}

		//collision by X axis stop the mario and dont accelerate
		if (nx != 0)
		{
			if (state.movement != MovingStates::Crouch)
				state.movement = MovingStates::Idle;
 			vx = 0;
			acc_x = 0;
		}
		if (ny != 0) {
			if (isOnGround)
				vy = 0;
			if (ny < 0)
			{
				// mario collide top down
				state.jump = JumpingStates::Stand;
				isOnGround = true;
				isHighJump = false;
			}
			else if (ny > 0)
			{
				// mario collide bottom up
				state.jump = JumpingStates::Fall;
				vy = 0;
			}
		}

	}

	if (vy > 0)
	{
		state.jump = JumpingStates::Fall;
		//isOnGround = false;
	}
	
	//if mario hold an object set the object with mario position;
	if (Hold != NULL)
	{
		if (direction == 1)
			Hold->setPosition(this->Position.x + 30, this->Position.y + 25);
		else
			Hold->setPosition(this->Position.x - 30, this->Position.y + 25);
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void MarioModel::setMovestate(MovingStates move)
{
	prestate = this->state;
	this->state.movement = move;

}

void MarioModel::setJumpstate(JumpingStates jump)
{
	switch (jump)
	{
	case JumpingStates::Fly:
		isOnGround = false;
		break;
	}
	this->state.jump = jump;
}

void MarioModel::OnKeyDown(int KeyCode)
{
	//Left = DIK_LEFT;
	//Right = DIK_RIGHT;
	//Jump = DIK_S;
	//Attack/Run = DIK_A;
	//LowJump = DIK_X;
	//Crouch = DIK_DOWN;
	switch (KeyCode)
	{
	case DIK_A:
	{
		IncreasePMetterTime_Start = GetTickCount();
	}
	case DIK_X:
		if (isOnGround)
		{
			setJumpstate(JumpingStates::Jump);
			isOnGround = false;
		}
		break;
	case DIK_S:
		if (isOnGround && state.jump != JumpingStates::Fall)
		{
				setJumpstate(JumpingStates::Jump);
				isOnGround = false;
				isHighJump = true;
				HighJumpTime_Start = GetTickCount();
				vy = MARIO_JUMP_FORCE;
		}
		break;
	//case DIK_A:
	//	this->state.movement = MovingStates::Run;
	//	break;
		
	case DIK_1:
		this->changestate = 0;
		break;
	
	case DIK_2:
		this->changestate = 1;
		break;

	case DIK_3:
		this->changestate = 2;
		break;
		
	case DIK_4:
		this->changestate = 3;
		break;
	case DIK_DOWN:
		setMovestate(MovingStates::Crouch);
		break;
	case DIK_Q:
	{
		FXObjectManager::GetInstance()->CreateFx("smoke", this->Position); 
		break;
	}
	case DIK_W:
	{
		GameObject* koop = new Koopa();

		Camera* cam = ScenceManager::GetInstance()->getCurrentScence()->getCamera();

		koop->setPosition(cam->getCameraPositionX(), cam->getCameraPositionY());
		ScenceManager::GetInstance()->getCurrentScence()->AddObject(koop);
		break;
	}
	}
}

void MarioModel::OnKeyUp(int keyCode)
{
	Game* game = Game::GetInstance();

	//if die disable controller
	if (this->state.movement == MovingStates::Die) return;

	switch (keyCode)
	{
	case DIK_S:
		if (isHighJump)
		{
			isHighJump = false;
		}
		break;
	case DIK_A:
		if (Hold != NULL)
		{
			if(this->direction == Hold->getDirection())
				Hold->setVx(-Hold->getVx());
			Hold->setIsBeingHold(false);
			Hold->setIsHoldAble(true);
			Hold = NULL;
		}
		DecayPMetterTime_Start = GetTickCount();
		break;
	}

}

void MarioModel::KeyState(BYTE* state)
{
	Game* game = Game::GetInstance();
	//if die disable controller
	if (this->state.movement == MovingStates::Die) return;

	if (game->IsKeyDown(DIK_RIGHT))
	{
		setMovestate(MovingStates::Walk);

		if (game->IsKeyDown(DIK_A))
		{
			setMovestate(MovingStates::Run);
		}

		acc_x = MARIO_ACCELERATION;
		direction = 1;
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		setMovestate(MovingStates::Walk);

		if (game->IsKeyDown(DIK_A))
		{
			setMovestate(MovingStates::Run);
		}

		acc_x = -MARIO_ACCELERATION;
		direction = -1;
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		setMovestate(MovingStates::Crouch);
	}
	else setMovestate(MovingStates::Idle);

	

	if (game->IsKeyDown(DIK_S))
	{
		if (isHighJump && this->state.jump != JumpingStates::Fall)
		{
			vy = MARIO_JUMP_FORCE;
		}
	}

	if (game->IsKeyDown(DIK_X))
	{
		if (isOnGround)
		{
			isOnGround = false;
			setJumpstate(JumpingStates::Jump);
			//vy = MARIO_JUMP_FORCE;
		}
		//if (isOnGround)
		//{
		//	setJumpstate(JumpingStates::Jump);
		//	isOnGround = false;
		//	vy = MARIO_JUMP_FORCE;
		//}
	}
	//DebugOut(L"[INFO] Moving: %i, Jumping: %i \n", this->state.movement, this->state.jump);
}

int MarioModel::getChangetoLevel()
{
	return this->changestate;
}

void MarioModel::SetChangetoLevel(int level)
{
	changestate = level;
}

void MarioModel::SetPosition(int x, int y)
{
	GameObject::setPosition(x, y);
}
