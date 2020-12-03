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
	
	//Textures::GetInstance()->AddTexture(40, L"textures\\Enemy\\enemy.png", NULL);
	//Textures::GetInstance()->AddTexture(30, L"textures\\Misc\\fire-ball.png", D3DCOLOR_ARGB(255, 255, 255, 255));
	//Textures::GetInstance()->AddTexture(20, L"textures\\Mario\\Mario48.png", NULL);
	//Textures::GetInstance()->AddTexture(100, L"textures\\bbox.png", NULL);
	//SpriteManager::GetInstance()->AddSpriteUsingXML("textures\\Enemy\\EnemyDB.xml", Textures::GetInstance()->GetTexture(40));
	//SpriteManager::GetInstance()->AddSpriteUsingXML("textures\\Mario\\MarioDB.xml", Textures::GetInstance()->GetTexture(20));
	//SpriteManager::GetInstance()->AddSpriteUsingXML("textures\\Misc\\MiscDB.xml", Textures::GetInstance()->GetTexture(30));
	//AnimationManager::GetInstance()->AddAnimationUsingXML("textures\\Enemy\\EnemyAnim.xml");
	//AnimationManager::GetInstance()->AddAnimationUsingXML("textures\\Mario\\MarioAnim.xml");
	//AnimationManager::GetInstance()->AddAnimationUsingXML("textures\\Misc\\MiscAnim.xml");

	//load Font

	tilemap = new Map();
	tilemap->LoadMapfromTMX("textures\\Map\\world-1-1-map.tmx", "textures\\Map\\");

	camera = new Camera();
	camera->setBound(0, 0, tilemap->getMapWidth(), tilemap->getMapHeight());
	
	mario = new Mario(100,1000);
	mario->setCamera(camera);
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


	if (earseobjects.size() > 0)
	{
		for (auto e : earseobjects)
		{
			for (size_t i = 0; i < objects.size(); i++)
			{
				if (objects[i] == e) objects.erase(objects.begin() + i);

				//cannot delete gameojbect pointer cause exception
				//e->~GameObject();
			}
		}
		earseobjects.clear();
	}


	if (camera->IsFollow())
		camera->setCameraPosition(mario->getX() - WINDOW_WIDTH / 2, mario->getY() - WINDOW_HEIGHT/2);/*800*/

	mario->Update(dt, &coObjects);
	camera->Update(dt);


}

void PlayScence::Render()
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
