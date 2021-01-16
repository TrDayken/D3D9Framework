#include "HUD.h"
#include "Global_Variable.h"
#include "Textures.h"
#include "SpriteManager.h"
#include "Game.h"
#include "ScenceManager.h"


HUD::HUD()
{
	auto sprite = SpriteManager::GetInstance();


	hud = SpriteManager::GetInstance()->GetSprite("spr-hud-0");

	metter = new PMetter(); 

	world = Vector2(32 + 110, WINDOW_HEIGHT - 150 + 24);
	life = Vector2(32 + 110 - 4, WINDOW_HEIGHT - 150 + 48);
	score = Vector2(32 + 147, WINDOW_HEIGHT - 150 + 48);
	coin = Vector2(32 + 400, WINDOW_HEIGHT - 150 + 24); 
	timer = Vector2(32 + 375, WINDOW_HEIGHT - 150 + 48);

	CardVisual[0] = sprite->GetSprite("spr-empty-card-0");
	CardVisual[1] = sprite->GetSprite("spr-super-mushroom-card-0");
	CardVisual[2] = sprite->GetSprite("spr-fire-flower-card-0");
	CardVisual[3] = sprite->GetSprite("spr-star-man-card-0");

	metter->setStaticPosition(Vector2(32 + 150, WINDOW_HEIGHT - 150 + 20));
}

HUD::~HUD()
{
}

void HUD::Update(DWORD dt)
{
	this->cards = Global_Variable::GetInstance()->getCardCarousel();
}

void HUD::Render()
{
	Game::GetInstance()->Draw(0, 594, Textures::GetInstance()->GetTexture("tex-pannel"), 0, 0, 824, 150);

	hud->Draw(0 + 32, WINDOW_HEIGHT - 150); 

	Game::GetInstance()->GetFont()->RenderText("1", world);
	Game::GetInstance()->GetFont()->RenderText(Global_Variable::GetInstance()->FormatLife(), life);
	Game::GetInstance()->GetFont()->RenderText(Global_Variable::GetInstance()->FormatScore(), score);
	Game::GetInstance()->GetFont()->RenderText(Global_Variable::GetInstance()->Formatcoin() , coin);
	Game::GetInstance()->GetFont()->RenderText(Global_Variable::GetInstance()->FormatTime(), timer);


	for (int i = cards.size() - 1; i >= 0; --i)
	{
		int x = WINDOW_WIDTH - CardVisual[i]->getSpriteWidth() * (cards.size() - i);
		int y = WINDOW_HEIGHT - 150;



		CardVisual[cards[i]]->Draw(x -32, y);
	}

	metter->Render();
}
