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
	addtoScenceManager();

	hud = new HUD(); 

	AddUI(hud);



	tilemap = new Map();
	tilemap->LoadMapfromTMX("textures\\Map\\world-1-1-map.tmx", "textures\\Map\\");

	camera = new Camera();
	camera->setBound(0, 0, tilemap->getMapWidth(), tilemap->getMapHeight());
	
	mario = new Mario(100,1000);
	mario->setCamera(camera);
	objects.push_back(mario); 
}

void PlayScence::Update(DWORD dt)
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


	if (camera->IsFollow())
		camera->setCameraPosition(mario->getX() - WINDOW_WIDTH / 2, mario->getY() - WINDOW_HEIGHT/2);/*800*/

	//mario->Update(dt, &coObjects);

	camera->Update(dt);


}

void PlayScence::Render()
{
	tilemap->Render(camera);

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render(camera);

		//float l, t, r, b;
		//objects[i]->GetBoundingBox(l, t, r, b);
		////DebugOut(L"[INFO] objects bounding box %f, %f, %f, %f \n", l, t, r, b);
	}

	//mario->Render(camera);

	for (size_t i = 0; i < UIElement.size(); i++)
	{
		UIElement[i]->Render();
	}
}

void PlayScence::Unload()
{

}

void PlayScence::addtoScenceManager()
{
	ScenceManager::GetInstance()->AddScence(this);
}

Camera* PlayScence::getCamera()
{
	return this->camera;
}

void PlayScenceKeyHandler::KeyState(BYTE* states)
{
	MarioModel* currentmario= ((PlayScence*)scence)->GetPlayer()->GetCurrentMario();

	currentmario->KeyState(states);
}

void PlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	MarioModel* currentmario = ((PlayScence*)scence)->GetPlayer()->GetCurrentMario();

	currentmario->OnKeyDown(KeyCode);
}

void PlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	MarioModel* currentmario = ((PlayScence*)scence)->GetPlayer()->GetCurrentMario();

	currentmario->OnKeyUp(KeyCode);
}
