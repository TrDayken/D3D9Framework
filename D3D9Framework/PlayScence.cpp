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

	Global_Variable::GetInstance()->setPlaystate(0);

	this->unload = false;

	hud = new HUD(); 

	AddUI(hud);

	tilemap = new Map();
	tilemap->LoadMapfromTMX(this->mapPath.c_str(), this->sceneFilePath.c_str());

	camera = new Camera();

	camera->setCameraPositionX(startx);
	camera->setCameraPositionY(starty);

	camera->setIsFollow(isfollow);
	camera->setIsStatic(isstatic);
	camera->setScrollX(scrollx);
	camera->setScrollY(scrolly);

	camera->setBound(boundl, boundt, boundr, boundb);
	
	auto node = split(this->mapPath, "\\");

	std::string gridfilepath = node[0] + "\\" + node[2] + "\\grid-" + node[4];

	grid = new Grid(tilemap->getMapWidth(), tilemap->getMapHeight());

	grid->DistributeGrid(objects, gridfilepath);

	mario = new Mario(100, 1000);
	mario->setCamera(camera);


	Global_Variable::GetInstance()->startGameTime();

}

void PlayScence::Update(DWORD dt)
{
	if (Global_Variable::GetInstance()->getPlaystate() == 1)
	{
		ScenceManager::GetInstance()->SwitchScence("world-map");
		return;
	}

	if (Global_Variable::GetInstance()->getPlaystate() == 2 && (GetTickCount() - Global_Variable::GetInstance()->getCycleTime() > 3000))
	{
		ScenceManager::GetInstance()->SwitchScence("world-map");
		return;
	}

	std::vector<LPGAMEOBJECT> coObjects;

	coObjects = objects; 

	grid->Update();

	activegameobject = grid->getActiveGameObject();
	activegameobject.push_back(mario);

	for (size_t i = 0; i < activegameobject.size(); i++)
	{
		if (unload) return;
		activegameobject[i]->Update(dt, &activegameobject);

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

	if (camera->IsStatic())
	{
		//	if (following_object->getX() < this->bound_left + 48)
		//	{
		//		following_object->setX(this->bound_left + 48);
		//		following_object->setVx(0.0f);
		//	}
		//	if (following_object->getX() + 48 > this->bound_right + WINDOW_WIDTH - 200)
		//	{
		//		following_object->setX(this->bound_right + WINDOW_WIDTH - 200);
		//		following_object->setVx(0.0f);
		//	}

		if (mario->GetCurrentMario()->getX() < camera->getCameraPositionX() )
		{
			mario->GetCurrentMario()->setX(camera->getCameraPositionX());
			//mario->setX(camera->getBoundleft() + 48);
		}
	}


	if (!camera->IsFollow() && !camera->IsStatic())
	{
		camera->setCameraPosition(6192 + 48, 1920);

		if (Global_Variable::GetInstance()->getSecret() == false)
		{
			camera->setIsFollow(true);
		}
	}


	if (camera->IsFollow() && !camera->IsStatic())
	{
		if (Global_Variable::GetInstance()->getSecret() == true)
		{
			camera->setIsFollow(false);
		}
		else if ((this->mario->GetCurrentMario()->getJumpState() == JumpingStates::Fly || this->mario->GetCurrentMario()->getJumpState() == JumpingStates::Float) || mario->getY() < jumpbound)
			camera->setCameraPosition(mario->getX() - WINDOW_WIDTH / 2, mario->getY() - WINDOW_HEIGHT / 2);/*800*/
		else 
			camera->setCameraPosition(mario->getX() - WINDOW_WIDTH / 2, 720);

	}

	//mario->Update(dt, &coObjects);

	camera->Update(dt);


}

void PlayScence::Render()
{
	if (unload) return;
	tilemap->Render(camera);

	//for (size_t i = 0; i < objects.size(); i++)
	//{
	//	objects[i]->Render(camera);
	//}

	for (size_t j = 0; j < LAYER_SIZE; j++)
	{
		for (int i = 0; (unsigned)i < activegameobject.size(); i++)
		{
			if (unload) return;
			if (activegameobject[i]->getRenderOrder() == j)
				activegameobject[i]->Render(camera);
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

Grid* PlayScence::getGrid()
{
	return this->grid;
}

void PlayScence::setGrid(Grid* grid)
{
	this->grid = grid; 
}

void PlayScence::AddObject(LPGAMEOBJECT object)
{
	grid->AddObject(object);
}

void PlayScence::DeleteObject(LPGAMEOBJECT object)
{
	grid->RemoveObject(object);
}

void PlayScence::setStartBound(int l, int r, int t, int b)
{
	this->boundl = l;
	this->boundr = r;
	this->boundt = t;
	this->boundb = b;
}

void PlayScence::setJumpBound(int j)
{
	this->jumpbound = j;
}

void PlayScence::setStartConfig(float startx, float starty, bool isstatic, bool isfollow, bool scrollx, bool scrolly)
{
	this->startx = startx;
	this->starty = starty;

	this->isstatic = isstatic;
	this->isfollow = isfollow;
	this->scrollx = scrollx;
	this->scrolly = scrolly;

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
