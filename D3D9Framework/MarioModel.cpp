#include "MarioModel.h"

MarioModel::MarioModel(float x, float y)
{
	start_x = x; 
	start_y = y;
	this->x = x; 
	this->y = y;

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

	

	if (x + dx <= 1)
	{
		dx = 0;
		x = 2;
		//DebugOut(L"[INFO] mario position %d, \n", x);
	}
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
		x += dx;
		y += dy;
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
			float px = x;
			x += min_ty * dx;
			y += min_ty * dy + ny * 0.4f;
			dy = 0;

			//DebugOut(L"		[X]point = : %f \n",px);
			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if (coEvents.size() > 0)
			{
				FilterCollisionX(coEvents, coEventsResult, min_tx, nx, rdx);
				//x -= min_ty * dx;
				x += min_tx * dx + nx * 0.4f;
				DebugOut(L"		[X] coEvents.size() = : %d \n", coEvents.size());
			}
			else
			{
				x = px + dx;
				nx = 0;
			}
			dy = vy * dt;

		}
		else
		{
			float py = y;
			x += min_tx * dx + nx * 0.4f;
			y += min_tx * dy;
			dx = 0;
			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if (coEvents.size() > 0)
			{
				FilterCollisionY(coEvents, coEventsResult, min_ty, ny, rdy);
				y += min_ty * dy + ny * 0.4f;
			}

			else
			{
				y = py + dy;
				ny = 0;
			}
			dx = vx * dt;
		}

		//collision by X axis stop the mario and dont accelerate
		if (nx != 0)
		{
 			vx = 0;
			acc_x = 0;
			//DebugOut(L"%f \n", acc_x);
			if (state.movement != MovingStates::Crouch)
				state.movement = MovingStates::Idle;
		}
		if (ny != 0) {
			vy = 0;
			if (ny < 0)
			{
				isOnGround = true;
				state.jump = JumpingStates::Stand;
				isHighJump = false;
			}
		}
	}

	

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void MarioModel::setMovestate(MovingStates move)
{
	prestate = this->state;
	this->state.movement = move;

	//if (state.movement == MovingStates::Crouch)
	//{
	//	if (prestate.movement != MovingStates::Crouch)
	//	{
	//		y += (MARIO_BBOX_HEIGHT - MARIO_BBOX_HEIGHT_CROUCH - 0.4);
	//	}
	//}
	//else
	//{
	//	if (prestate.movement == MovingStates::Crouch)
	//	{
	//		y -= (MARIO_BBOX_HEIGHT - MARIO_BBOX_HEIGHT_CROUCH + 0.4);
	//	}
	//}
}

void MarioModel::setJumpstate(JumpingStates jump)
{
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
	case DIK_X:
		if (isOnGround)
		{
			setJumpstate(JumpingStates::Jump);
			isOnGround = false;
		}
		break;
	case DIK_S:
		if (isOnGround)
		{
			setJumpstate(JumpingStates::Jump);
			isOnGround = false;
			isHighJump = true;
			HighJumpTime_Start = GetTickCount();
			vy = MARIO_MINIMUM_LIFT;
		}
	//case DIK_A:
	//	this->state.movement = MovingStates::Run;
	//	break;
		
	case DIK_F1:

		break;
	
	case DIK_F2:

		break;

	case DIK_F3:

		break;
		
	case DIK_F4:
		break;
	case DIK_DOWN:
		setMovestate(MovingStates::Crouch);
		break;
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
		if (isHighJump)
		{
			vy = MARIO_JUMP_FORCE;
		}
	}

	if (game->IsKeyDown(DIK_X))
	{
		if (isOnGround)
		{
			isOnGround = false;
			vy = MARIO_JUMP_FORCE;
			setJumpstate(JumpingStates::Jump);
		}
		//if (isOnGround)
		//{
		//	setJumpstate(JumpingStates::Jump);
		//	isOnGround = false;
		//	vy = MARIO_JUMP_FORCE;
		//}
	}
	DebugOut(L"[INFO] Moving: %i, Jumping: %i \n", this->state.movement, this->state.jump);
}
