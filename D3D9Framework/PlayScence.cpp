#include "PlayScence.h"

PlayScence::PlayScence()
{
	key_handler = new PlayScenceKeyHandler(this);
}

PlayScence::PlayScence(std::string id, std::string mappath, std::string filepath) : Scence(id, mappath, filepath)
{
	key_handler = new PlayScenceKeyHandler(this);
}


void PlayScence::Load()
{



	this->unload = false;

	hud = new HUD(); 

	AddUI(hud);

	mario = new Mario(100, 1000);
	mario->setCamera(camera);
	objects.push_back(mario);

	tilemap = new Map();
	tilemap->LoadMapfromTMX(this->mapPath.c_str(), this->sceneFilePath.c_str());

	camera = new Camera();
	camera->setBound(0, 0, tilemap->getMapWidth(), tilemap->getMapHeight());

	grid = new Grid(6000, 6000);
	

	Global_Variable::GetInstance()->startGameTime();

}

void PlayScence::Update(DWORD dt)
{
	std::vector<LPGAMEOBJECT> coObjects;

	coObjects = objects; 

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (unload) return;
		objects[i]->Update(dt, &coObjects);
		
	}

	for (size_t i = 0; i < UIElement.size(); i++)
	{
		if (unload) return;
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

	grid->Update();

	bool isfollow = false; 

	if (!camera->IsFollow())
	{
		camera->setCameraPosition(6192 + 48, 1920);

		if (Global_Variable::GetInstance()->getSecret() == false)
		{
			camera->setIsFollow(true);
		}
	}


	if (camera->IsFollow())
	{
		if (Global_Variable::GetInstance()->getSecret() == true)
		{
			camera->setIsFollow(false);
		}
		else if ((this->mario->GetCurrentMario()->getJumpState() == JumpingStates::Fly || this->mario->GetCurrentMario()->getJumpState() == JumpingStates::Float) || mario->getY() < 600 || mario->getY() > 1300)
			camera->setCameraPosition(mario->getX() - WINDOW_WIDTH / 2, mario->getY() - WINDOW_HEIGHT / 2);/*800*/
		else 
			camera->setCameraPosition(mario->getX() - WINDOW_WIDTH / 2, 720);

	}

	//mario->Update(dt, &coObjects);

	camera->Update(dt);


}

void PlayScence::Render()
{
	tilemap->Render(camera);

	//for (size_t i = 0; i < objects.size(); i++)
	//{
	//	objects[i]->Render(camera);
	//}

	for (size_t j = 0; j < LAYER_SIZE; j++)
	{
		for (int i = 0; (unsigned)i < objects.size(); i++)
		{
			if (objects[i]->getRenderOrder() == j)
				objects[i]->Render(camera);
		}
	}



	for (size_t i = 0; i < UIElement.size(); i++)
	{
		UIElement[i]->Render();
	}
}

void PlayScence::Unload()
{
	this->unload = true; 

	for (int i = 0; (unsigned)i < objects.size(); i++)
		delete objects[i];

	objects.clear();

	for (int i = 0; (unsigned)i < UIElement.size(); i++)
		delete UIElement[i];
	UIElement.clear();

	tilemap->Unload();

	this->camera->~Camera();

	//delete uiobject

	this->mario->Unload();

	mario = NULL;

	DebugOut(L"[UNLOADED] PlayScence has unloaded \n");
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
