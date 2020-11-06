#include "Mario.h"

Mario::Mario(float x, float y)
{
	AnimationLoad();
	
	this->start_x = x; 
	this->start_y = y;

	this->x = x;
	this->y = y;


	StateofMario.push_back(new SmallMario());
	StateofMario.push_back(new BigMario());

	CurrentMario = StateofMario[1];
	CurrentMario->setPosition(x, y);
}

void Mario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects)
{
	//call update on specific mario
	CurrentMario->Update(dt, collision_objects);
	//after update need to reupdate the mariostate position to mario to render camera;
	this->setPosition(CurrentMario->getX(), CurrentMario->getY());

	///*if (x < camera->getBoundleft() - 48)
	//	x = camera->getBoundleft() - 48;
	//if (x + 48 > camera->getBoundRight() + WINDOW_WIDTH)
	//	x = (float)(camera->getBoundRight() + WINDOW_HEIGHT - 48);*/

	//GameObject::Update(dt);

	//vy = MARIO_GRAVITY * dt;

	////DebugOut(L"[INFO] Mario position x: %f , y: %f \n", this->x , this ->y);

	//std::vector<LPCOLLISIONEVENT> coEvents;
	//std::vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	//CalcPotentialCollisions(collision_objects, coEvents);

	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//	y += dy;
	//	
	//	//DebugOut(L"[info] detect colision\n");
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;
	//	float rdx = 0;
	//	float rdy = 0;

	//	// TODO: This is a very ugly designed function!!!!
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
	//	//if (rdx != 0 && rdx!=dx)
	//	//	x += nx*abs(rdx); 

	//	// block every object first!
	//	x += min_tx * dx + nx * 0.4f;
	//	y += min_ty * dy + ny * 0.4f;
	//	vy = 0;
	//	if (nx != 0) vx = 0;
	//	if (ny != 0) vy = 0;
	//}
}

//void Mario::Render()
//{
//	animation_set.at(1)->Render(this->start_x,this->start_y);
//}

void Mario::Render(Camera* camera)
{
	CurrentMario->Render(camera);
}

void Mario::SetState(int state)
{
}

MarioModel* Mario::GetCurrentMario()
{
	return this->CurrentMario;
}

void Mario::Reset()
{
}

void Mario::AnimationLoad()
{
	//LPANIMATION ani = AnimationManager::GetInstance()->GetAnimation("ani-small-mario-walk");
	//animation_set.push_back(ani);
	//ani = AnimationManager::GetInstance()->GetAnimation("ani-big-mario-walk");
	//animation_set.push_back(ani);
}

void Mario::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	this->CurrentMario->GetBoundingBox(left, top, right, bottom);
}
