#include "PSwitch.h"
#include "AnimationManager.h"
#include "Global_Variable.h"

PSwitch::PSwitch()
{
	LoadAnimation();

	ColTag = Collision2DTag::FourSide;

	EntityTag = Tag::pswitch;

	ispressed  = false; 

	DebugOut(L"[INFO] pswitch created \n");

	this->setRenderOrder(1);
}

void PSwitch::LoadAnimation()
{
	auto animation = AnimationManager::GetInstance();

	AddAnimation("Default", animation->GetAnimation("ani-switch-block"));
	AddAnimation("Pressed", animation->GetAnimation("ani-switch-block-pressed"));
}

void PSwitch::Render(Camera* camera)
{

	GameObject::Render(camera);

	std::string animation = "Default";

	if (ispressed) animation = "Pressed";

	animation_set[animation]->Render(RenderPosition.x, RenderPosition.y);
}

void PSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (ispressed == true) return;

	l = this->Position.x;
	t = this->Position.y;
	r = this->Position.x + PSWITCH_BBOX_WIDTH;
	b = this->Position.y + PSWITCH_BBOX_HEIGHT;
}

void PSwitch::OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny)
{
	if (obj->EntityTag == Tag::player && ny < 0)
	{
		Global_Variable* var = Global_Variable::GetInstance();

		var->startPtime();

		this->RelativePosition = Vector2(0, PSWITCH_BBOX_HEIGHT - PSWITCH_PRESSED_BBOX_HEIGHT);
		this->ispressed = true;
	}
}

void PSwitch::OnOverLap(GameObject* obj)
{

}

void PSwitch::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	//if (Global_Variable::GetInstance()->isPtimeUp())
	//{
	//	DebugOut(L"[INFO] Ptime Left %d \n", Global_Variable::GetInstance()->getPTimeLeft());
	//}

}
