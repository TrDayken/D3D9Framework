#pragma once

#include <unordered_map>
#include <d3dx9.h>

using namespace std;

class Textures
{
private:
	static Textures* __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:
	Textures();

	void AddTexture(int id, LPCWSTR filePath, D3DCOLOR TransColor);
	LPDIRECT3DTEXTURE9 GetTexture(unsigned int i);

	static Textures* GetInstance();
};

