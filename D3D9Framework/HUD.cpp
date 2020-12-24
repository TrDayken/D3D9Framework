#include "HUD.h"
#include "Global_Variable.h"
#include "Textures.h"
#include "SpriteManager.h"
#include "Game.h"

HUD::HUD()
{

	hud = SpriteManager::GetInstance()->GetSprite("spr-hud-0");

	metter = new PMetter(); 

	world = Vector2(32 + 110, WINDOW_HEIGHT - 150 + 24);
	life = Vector2(32 + 110 - 4, WINDOW_HEIGHT - 150 + 48);
	score = Vector2(32 + 147, WINDOW_HEIGHT - 150 + 48);
	coin = Vector2(32 + 400, WINDOW_HEIGHT - 150 + 24); 
	timer = Vector2(32 + 375, WINDOW_HEIGHT - 150 + 48);

	metter->setStaticPosition(Vector2(32 + 150, WINDOW_HEIGHT - 150 + 20));
}

HUD::~HUD()
{
}

void HUD::Update(DWORD dt)
{
}

void HUD::Render()
{
	Game::GetInstance()->Draw(0, 580, Textures::GetInstance()->GetTexture("tex-pannel"), 0, 0, 824, 150);

	hud->Draw(0 + 32, WINDOW_HEIGHT - 150); 


	Game::GetInstance()->GetFont()->RenderText("1", world);
	Game::GetInstance()->GetFont()->RenderText("4", life);
	Game::GetInstance()->GetFont()->RenderText("0002340", score);
	Game::GetInstance()->GetFont()->RenderText("11", coin);
	Game::GetInstance()->GetFont()->RenderText("000", timer);

	metter->Render();
}
