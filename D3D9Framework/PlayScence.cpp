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

	camera = new Camera();
	camera->setBound(0, 0, tilemap->getMapWidth(), tilemap->getMapHeight());

	mario = new Mario(100,100);
}

void PlayScence::Update(DWORD dt)
{
	camera->Update(dt);
}

void PlayScence::Render()
{
	tilemap->Render(camera);
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
