#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include <unordered_map>
#include <d3dx9.h>

#include "Utils.h"
#include "SpriteManager.h"
#include "AnimationManager.h"

class Textures
{
private:
	static Textures* __instance;

	std::unordered_map<std::string, LPDIRECT3DTEXTURE9> textures;

public:
	Textures();

	void AddTexture(std::string id, LPCWSTR filePath, D3DCOLOR TransColor);

	LPDIRECT3DTEXTURE9 GetTexture(std::string id);

	void LoadResource();

	static Textures* GetInstance();
};

#endif 