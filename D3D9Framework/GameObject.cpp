#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{
	this->RenderPosition = VectorZero;
	this->RelativePosition = VectorZero;
	this->Position.x = this->Position.y = 0;
	this->Scale = Vector2(1.0, 1.0);
	vx = vy = 0;
	direction = 1;
	flipy = 1;
}

GameObject::~GameObject()
{
	animation_set.clear();
}

void GameObject::setPosition(float x, float y)
{
	this->Position.x = x; 
	this->Position.y = y;
}

void GameObject::getPosition(float& x, float& y)
{
	x = this->Position.x;
	y = this->Position.y;
}

void GameObject::setRelativePosition(float x, float y)
{
	this->RelativePosition.x = x; 
	this->RelativePosition.y = y;
}

void GameObject::getRelativePosition(float& x, float& y)
{
	x = RelativePosition.x; 
	y = RelativePosition.y;
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

void GameObject::setIsBeingHold(bool isBeingHold)
{
	this->isBeingHold = isBeingHold;
}

bool GameObject::IsHoldAble()
{
	return isHoldAble;
}

void GameObject::setIsHoldAble(bool ishold)
{
	isHoldAble = ishold;
}

float GameObject::getX()
{
	return this->Position.x;
}

void GameObject::setX(float x)
{
	this->Position.x = x;
}

float GameObject::getY()
{
	return this->Position.y;
}

void GameObject::setY(float y)
{
	this->Position.y = y;
}

float GameObject::getVx()
{
	return this->vx;
}

void GameObject::setVx(float vx)
{
	this->vx += vx;
}

float GameObject::getVy()
{
	return this->vy;
}

void GameObject::setVy(float vy)
{
	this->vy += vy;
}

float GameObject::getWidth()
{
	return this->width;
}

void GameObject::setWidth(float width)
{
	this->width = width;
}

float GameObject::getHeight()
{
	return this->height;
}

void GameObject::setHeight(float height)
{
	this->height = height;
}

void GameObject::setDirection(int direction)
{
		this->direction = direction;
}

int GameObject::getDirection()
{
	return this->direction;
}

int GameObject::getState()
{
	return 0;
}

void GameObject::RenderBoundingBox(Camera* camera)
{
	RECT rect;
	float l, t, r, b;

	Vector2 camPos = camera->toCameraPosistion(this->Position.x, this->Position.y);
	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->GetTexture("tex-bbox");

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0; 
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	Game::GetInstance()->Draw(camPos.x, camPos.y ,bbox, rect.left, rect.top, rect.right, rect.bottom, 112);

}

void GameObject::AddAnimation(std::string name, LPANIMATION animation)
{
	animation_set[name] = animation;
}

void GameObject::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

void GameObject::Render(Camera* camera)
{
	Vector2 pos = camera->toCameraPosistion(this->Position.x, this->Position.y);

	this->RenderPosition = pos + RelativePosition;
}



bool GameObject::IsOverLapped(GameObject* object)
{
	float left, top, right, bottom;
	float left1, top1, right1, bottom1;

	this->GetBoundingBox(left, top, right, bottom);
	object->GetBoundingBox(left1, top1, right1, bottom1);

	return CheckOverlapped(left, top, right, bottom, left1, top1, right1, bottom1);
}

bool GameObject::CheckOverlapped(float left, float top, float right, float bottom, float left1, float top1, float right1, float bottom1)
{
	if (left >= right1 || left1 >= right || top >= bottom1 || top1 >= bottom)
		return false;

	return true;
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

		if(IsOverLapped(coObjects->at(i)))
		{
			this->OnOverLap(coObjects->at(i));
			coObjects->at(i)->OnOverLap(this);
		}

		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));


		if (e->t > 0 && e->t <= 1.0f)
		{
			
			float ml = 0, mt = 0, mr = 0, mb = 0;
			// check for collisiont tag and collide direction if match then create the event!!!
			e->obj->GetBoundingBox(ml, mt, mr, mb);
			if (e->obj->ColTag == Collision2DTag::FourSide)
				coEvents.push_back(e);

			else if (e->ny < 0 && e->obj->ColTag == Collision2DTag::Top)
				coEvents.push_back(e);

		}
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

void GameObject::FilterCollisionX(std::vector<LPCOLLISIONEVENT>& coEvents,
	std::vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, 
	float& nx, float& rdx)
{
	min_tx = 1.0f;
	int min_ix = -1;
	nx = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
}

void GameObject::FilterCollisionY(std::vector<LPCOLLISIONEVENT>& coEvents,
	std::vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_ty,
	float& ny, float& rdy)
{
	min_ty = 1.0f;
	int min_iy = -1;

	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}