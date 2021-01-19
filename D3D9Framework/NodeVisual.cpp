#include "NodeVisual.h"
#include "SpriteManager.h"

NodeVisual::NodeVisual()
{
	this->LoadAnimation();
}

void NodeVisual::LoadAnimation()
{
	auto sprite = SpriteManager::GetInstance();

	visual[0] = sprite->GetSprite("spr-start-0");
	visual[1] = sprite->GetSprite("spr-gate-1");
	visual[2] = sprite->GetSprite("spr-gate-2");
	visual[3] = sprite->GetSprite("spr-gate-3");
	visual[4] = sprite->GetSprite("spr-gate-4");
	visual[5] = sprite->GetSprite("spr-gate-5");
	visual[6] = sprite->GetSprite("spr-gate-6");
	visual[7] = sprite->GetSprite("spr-spade-0");

	number = 0;
}

void NodeVisual::Render(Camera* camera)
{
	if (number >= 8)return;

	GameObject::Render(camera);

	visual[number]->Draw(RenderPosition.x, RenderPosition.y);
}

void NodeVisual::SetNumber(int value)
{
	this->number = value;
}

void NodeVisual::setScenceID(std::string id)
{
	this->sceneID = id;
}
