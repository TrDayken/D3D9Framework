#include "ScoreFx.h"
#include "SpriteManager.h"
#include "ScenceManager.h"

void ScoreFx::LoadAnimation()
{
	std::string prefix = "spr-points-in-level-";

	std::string suffix[9] = { "100", "200", "400", "800", "1000", "2000", "4000", "8000", "1UP" };
	for (int i = 0; i < 9; ++i)
		score[i] = SpriteManager::GetInstance()->GetSprite(prefix + suffix[i]);
}

ScoreFx::ScoreFx()
{
	LoadAnimation();

	level = 0;

	speed = -FLOAT_SPEED;

	this->setRenderOrder(5);
}

void ScoreFx::setLevel(int level)
{
	this->level = level;
}

void ScoreFx::Render(Camera* camera)
{
	if (level >= 9) return; 
	Vector2 pos = camera->toCameraPosistion(Position.x, Position.y);

	score[level]->Draw(pos.x, pos.y);
}

void ScoreFx::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	this->dy = speed * dt;

	this->Position.y += dy; 

	speed += DRAG * dt; 

	if (speed >= 0)
		ScenceManager::GetInstance()->getCurrentScence()->DeleteObject(this);
}
