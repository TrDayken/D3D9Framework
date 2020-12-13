#include "Textures.h"
#include "Game.h"
#include "Debug.h"

Textures* Textures::__instance = nullptr;

Textures::Textures()
{
}

void Textures::AddTexture(std::string id, LPCWSTR filePath, D3DCOLOR TransColor)
{
	textures[id] = Game::GetInstance()->LoadTexture(filePath, TransColor);
}

LPDIRECT3DTEXTURE9 Textures::GetTexture(std::string id)
{
	return textures[id];
}

void Textures::LoadResource()
{
	SpriteManager* spritemanager = SpriteManager::GetInstance();
	AnimationManager* animationmanager = AnimationManager::GetInstance();

	//add sprite and animation for mario
	//this->AddTexture(20, L"textures\\Mario\\Mario48.png", D3DCOLOR_XRGB(255,255,255));
	//spritemanager->AddSpriteUsingXML("textures\\Mario\\MarioDB.xml", this->GetTexture(20));
	//animationmanager->AddAnimationUsingXML("textures\\Mario\\MarioAnim.xml");
}

Textures* Textures::GetInstance()
{
	if (__instance == NULL)
		__instance = new Textures();
	return __instance;
}
