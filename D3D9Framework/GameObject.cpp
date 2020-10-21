#include "GameObject.h"

void GameObject::setPosition(float x, float y)
{
	this->x = x; 
	this->y = y;
}

void GameObject::getPosition(float& x, float& y)
{
	x = this->x;
	y = this->y;
}

void GameObject::setSpeed(float vx, float vy)
{
	this->vx = vx;
	this->vy = vy;
}

void GameObject::GetSpeed(float& vx, float& vy)
{
	vx = this->vx;
	vy = this->vy;
}

float GameObject::getX()
{
	return this->x;
}

void GameObject::setX(float x)
{
	this->x = x;
}

float GameObject::getY()
{
	return this->y;
}

void GameObject::setY(float y)
{
	this->y = y;
}

float GameObject::getVx()
{
	return this->vx;
}

void GameObject::setVx(float vx)
{
}

float GameObject::getVy()
{
	return this->vy;
}

void GameObject::setVy(float vy)
{
	this->vy = vy;
}

void GameObject::setDirection(int direction)
{
	if (direction != 0 && direction != 1)
	{
		direction = 1;
	}
	else
	{
		this->direction = direction;
	}
}

int GameObject::getDirection()
{
	return this->direction;
}

int GameObject::getState()
{
	return 0;
}

void GameObject::RenderBoundingBox()
{
	RECT rect;
	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0; 
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	//Game::GetInstance()->Draw(x, y, /*bbox texture */, rect.left, rect.top, rect.right, rect.bottom, 32);

}

void GameObject::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	Game::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

void GameObject::CalcPotentialCollisions(std::vector<LPGAMEOBJECT>* coObjects, std::vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void GameObject::FilterCollision(std::vector<LPCOLLISIONEVENT>& coEvents, std::vector<LPCOLLISIONEVENT>& coEventsResult, float& min_tx, float& min_ty, float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}
