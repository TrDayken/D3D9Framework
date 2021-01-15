#include "RedMushroomPowerUps.h"
#include "AnimationManager.h"
#include "MarioModel.h"
#include "FXObjectManager.h"
#include "ScoreFx.h"

void RedMushroomPowerUps::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("Idle", animation->GetAnimation("ani-super-mushroom"));

}

RedMushroomPowerUps::RedMushroomPowerUps()
{
	LoadAnimation();

	this->ColTag = Collision2DTag::None;

	RelativePosition = Vector2(0, 48);

	state = 1;

	this->EntityTag = Tag::mushroom;
}

void RedMushroomPowerUps::Render(Camera* camera)
{
	GameObject::Render(camera);

	animation_set["Idle"]->Render(RenderPosition.x, RenderPosition.y);
}

void RedMushroomPowerUps::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = Position.x; 
	t = Position.y;
	r = Position.x + MUSHROOM_WIDTH;
	b = Position.y + MUSHROOM_HEIGHT;
}

void RedMushroomPowerUps::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObject)
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

		if (ny != 0) vy = 0;

		if (nx != 0)
			direction = -direction; 

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	switch (state)
	{
	case 1:
	{
		RelativePosition.y -= SPROUT_SPEED * dt;
		if (RelativePosition.y < 0)
		{
			RelativePosition.y = 0;
			state = 2;
		}
	}
	break;
	case 2:
	{
		vx = MUSHROOM_SPEED * direction;
		vy += MUSHROOM_GRAVITY * dt;
	}
	break;
	}


}

void RedMushroomPowerUps::OnOverLap(GameObject* obj)
{

	if (obj->EntityTag == Tag::player)
	{

		ScoreFx* score = static_cast<ScoreFx*>(FXObjectManager::GetInstance()->CreateFx("score", this->Position));
		score->setLevel(4);
		Global_Variable::GetInstance()->AddScore(1000);
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this); 
	}
}
