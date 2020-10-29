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
	Textures::GetInstance()->AddTexture(20, L"textures\\Mario\\Mario48.png", NULL);
	SpriteManager::GetInstance()->AddSpriteUsingXML("textures\\Mario\\MarioDB.xml", Textures::GetInstance()->GetTexture(20));
	AnimationManager::GetInstance()->AddAnimationUsingXML("textures\\Mario\\MarioAnim.xml");

	tilemap = new Map();
	tilemap->LoadMapfromTMX("textures\\Map\\world-1-1-map.tmx", "textures\\Map\\");
	tilemap->setObjectonLayer(&objects, "Ground");

	mario = new Mario(100,1000);

	camera = new Camera();
	camera->setBound(0, 0, tilemap->getMapWidth(), tilemap->getMapHeight());
	camera->FollowObject(mario);
}

void PlayScence::Update(DWORD dt)
{
	std::vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		
		objects[i]->Update(dt, &coObjects);
		
	}

	camera->Update(dt);

	mario->Update(dt, &coObjects);
}

void PlayScence::Render()
{
	tilemap->Render(camera);

	mario->Render(camera);

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
		float l, t, r, b;
		objects[i]->GetBoundingBox(l, t, r, b);
		DebugOut(L"[INFO] objects bounding box %f, %f, %f, %f \n", l, t, r, b);
	}
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
