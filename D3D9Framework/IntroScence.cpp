#include "IntroScence.h"
#include "ScenceManager.h"

IntroScence::IntroScence()
{
}

IntroScence::IntroScence(std::string id, std::string mappath, std::string filepath) :Scence(id, mappath, filepath)
{
	key_handler = new IntroKeyHandler(this);
}

IntroScence::~IntroScence()
{
}

void IntroScence::Load()
{
	curtain = new Curtain();
	three = new NumberThree();

	Option = SpriteManager::GetInstance()->GetSprite("spr-options-0");
	Arrow = SpriteManager::GetInstance()->GetSprite("spr-menu-arrow-0");

	tilemap = new Map();
	tilemap->LoadMapfromTMX(this->mapPath.c_str(), this->sceneFilePath.c_str());

	camera = new Camera();
	camera->setBound(0, 0, tilemap->getMapWidth(), tilemap->getMapHeight());

	option = Vector2(225, 375);
	arrow = Vector2(175, 375);
}

void IntroScence::Update(DWORD dt)
{
	camera->Update(dt);


	curtain->Update(dt);
	three->Update(dt);
}

void IntroScence::Render()
{
	tilemap->Render(camera);

	Option->Draw(option.x, option.y);
	if (Global_Variable::GetInstance()->getIntroInstance() == 0)
		Arrow->Draw(arrow.x, arrow.y);
	else
		Arrow->Draw(arrow.x, arrow.y +50);

	three->Render(camera);
	curtain->Render(camera);
}

void IntroScence::Unload()
{
	Option = NULL;
	Arrow = NULL;
}

void IntroScence::addtoScenceManager()
{
}

Camera* IntroScence::getCamera()
{
	return nullptr;
}

void IntroKeyHandler::KeyState(BYTE* states)
{
}

void IntroKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_DOWN:
	case DIK_UP:
		Global_Variable::GetInstance()->Downintro();
		break;
	case DIK_A:
	{
		ScenceManager::GetInstance()->SwitchScence("world-map");
	}
	break;
	default:
		break;
	}
}

void IntroKeyHandler::OnKeyUp(int KeyCode)
{
}
