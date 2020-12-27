#include "MapScence.h"
#include "ScenceManager.h"

MapScence::MapScence()
{
	key_handler = new MapScenceKeyHandler(this);
}

MapScence::~MapScence()
{
}

void MapScence::Load()
{
	addtoScenceManager();

	hud = new HUD();

	AddUI(hud);

	tilemap = new Map();
	tilemap->LoadMapfromTMX("textures\\Map\\overworld-1-map.tmx", "textures\\Map\\");

	camera = new Camera();
	camera->setBound(0, 0, tilemap->getMapWidth(), tilemap->getMapHeight());

	mario = new MapMario();
	//mario->setCamera(camera);
}

void MapScence::Update(DWORD dt)
{
	std::vector<LPGAMEOBJECT> coObjects;

	coObjects = objects;

	for (size_t i = 0; i < objects.size(); i++)
	{

		objects[i]->Update(dt, &coObjects);

	}

	for (size_t i = 0; i < UIElement.size(); i++)
	{
		UIElement[i]->Update(dt);
	}

	//if object in erase vector delete it
	if (earseobjects.size() > 0)
	{
		for (auto e : earseobjects)
		{
			for (size_t i = 0; i < objects.size(); i++)
			{
				if (objects[i] == e)
				{
					objects.erase(objects.begin() + i);
				}

				//delete this gameojbect pointer cause exception why??
				//e->~GameObject();
			}
		}
		earseobjects.clear();
	}

	mario->Update(dt, &coObjects);

	camera->Update(dt);

}

void MapScence::Render()
{
	tilemap->Render(camera);

	mario->Render(camera);

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render(camera);

		//float l, t, r, b;
		//objects[i]->GetBoundingBox(l, t, r, b);
		////DebugOut(L"[INFO] objects bounding box %f, %f, %f, %f \n", l, t, r, b);
	}

	for (size_t i = 0; i < UIElement.size(); i++)
	{
		UIElement[i]->Render();
	}
}

void MapScence::Unload()
{
}

void MapScence::addtoScenceManager()
{
	ScenceManager::GetInstance()->AddScence(this);
}

Camera* MapScence::getCamera()
{
	return this->camera;
}

void MapScenceKeyHandler::KeyState(BYTE* states)
{

}

void MapScenceKeyHandler::OnKeyDown(int KeyCode)
{
	((MapScence*)scence)->GetPlayer()->OnKeyDown(KeyCode);
}

void MapScenceKeyHandler::OnKeyUp(int KeyCode)
{
}
