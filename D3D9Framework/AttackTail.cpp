#include "AttackTail.h"

AttackTail::AttackTail(float x, float y, int direction)
{
	Deletetime = GetTickCount();
	EntityTag = Tag::tail;
	ColTag = Collision2DTag::None;
	this->Position.x = x; 
	this->Position.y = y;
	direction = 1;
}
	
void AttackTail::Render(Camera* camera)
{
	//RenderBoundingBox(camera);
}

void AttackTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + ATTACKTAIL_BBOX_WIDTH;
	b = this->Position.y + ATTACKTAIL_BBOX_HEIGHT;
}

void AttackTail::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObject)
{
	GameObject::Update(dt);

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObject, coEvents);

	if (coEvents.size() == 0)
	{
		this->Position.x += dx;
		this->Position.y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		this->Position.x += min_tx * dx + nx * 0.4;
		this->Position.y += min_ty * dy + ny * 0.4;

		

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->EntityTag == Tag::enemy)
			{
				LPGAMEOBJECT obj = e->obj;
				obj->OnCollisionEnter(this, e->nx, e->ny);
				ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
			}
			else if (e->nx != 0 && nx != 0) ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (GetTickCount() - Deletetime > RACOON_ATTACK_ANI_TIME)
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
}

void AttackTail::OnOverLap(GameObject* obj)
{
	if (obj->EntityTag == Tag::enemy)
	{
		obj->OnOverLap(this);
	}
}

void AttackTail::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
}
