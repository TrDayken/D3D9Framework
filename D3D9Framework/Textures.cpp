#include "Textures.h"
#include "Game.h"
#include "Debug.h"

Textures* Textures::__instance = nullptr;

Textures::Textures()
{
}

void Textures::AddTexture(int id, LPCWSTR filePath, D3DCOLOR TransColor)
{
	textures[id] = Game::GetInstance()->LoadTexture(filePath);
}

LPDIRECT3DTEXTURE9 Textures::GetTexture(unsigned int i)
{
	return textures[i];
}

Textures* Textures::GetInstance()
{
	if (__instance == NULL)
		__instance = new Textures();
	return __instance;
}
