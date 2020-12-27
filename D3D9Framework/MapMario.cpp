#include "MapMario.h"
#include "AnimationManager.h"

void MapMario::LoadAnimation()
{
	auto animations = AnimationManager::GetInstance();

	AddAnimation("SmallMario", animations->GetAnimation("ani-small-mario-map"));
	AddAnimation("BigMario", animations->GetAnimation("ani-big-mario-map"));
	AddAnimation("RaccoonMario", animations->GetAnimation("ani-raccoon-mario-map"));
	AddAnimation("FireMario", animations->GetAnimation("ani-fire-mario-map"));
}

MapMario::MapMario()
{
	LoadAnimation();

	ismoving = false;
}

MapMario::~MapMario()
{
}

void MapMario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects)
{

}

void MapMario::Render(Camera* camera)
{
}

void MapMario::OnKeyDown(int KeyCode)
{
	//DIK_A: SELECT
	//DIK_UP,_DOWN_LEFT_RIGHT: MOVE TO NODE;
}
