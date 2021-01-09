#include "VenusFireShoot.h"

VenusFireShoot::VenusFireShoot(float x, float y, int direction, int vertical )
{
	ColTag == Collision2DTag::None;

	EntityTag = Tag::enemyprojectile;

	this->Position.x = x;
	this->Position.y = y;
	vx = BULLET_VX * direction;
	vy = BULLET_VY * vertical;
	LoadAnimation();
}

VenusFireShoot::~VenusFireShoot()
{

}

void VenusFireShoot::Render(Camera* camera)
{
	Vector2 camPos = camera->toCameraPosistion(this->Position.x, this->Position.y);

	std::string ani = ANI_BULLET;

	animation_set[ani]->Render(camPos.x, camPos.y, this->Scale, direction);
}

void VenusFireShoot::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + BULLET_BBOX_WIDTH;
	b = this->Position.y + BULLET_BBOX_HEIGHT;
}

void VenusFireShoot::LoadAnimation()
{
	AnimationManager* animation = AnimationManager::GetInstance();

	AddAnimation(ANI_BULLET, animation->GetAnimation(ANI_BULLET));
}

void VenusFireShoot::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	this->Position.x += dx;
	this->Position.y += dy;
}

void VenusFireShoot::OnOverLap(GameObject* object)
{
}
