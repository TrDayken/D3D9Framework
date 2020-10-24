#include "PlayScence.h"

PlayScence::PlayScence()
{
	key_handler = new PlayScenceKeyHandler(this);
}

PlayScence::PlayScence(int id, LPCWSTR filePath) : Scence(id, filePath)
{ 
	key_handler = new PlayScenceKeyHandler(this);
}

void PlayScence::Load()
{
	tilemap = new Map();
	tilemap->LoadMapfromTMX("textures\\Map\\world-1-1-map.tmx", "textures\\Map\\");
}

void PlayScence::Update(DWORD dt)
{
}

void PlayScence::Render()
{
	tilemap->Render();
}

void PlayScence::Unload()
{
}

void PlayScenceKeyHandler::KeyState(BYTE* states)
{
}

void PlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
}
