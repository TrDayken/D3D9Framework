#pragma once
#include "Scence.h"
#include "Map.h"
#include "FrontIntro.h"
#include "Curtain.h"
#include "NumberThree.h"

class IntroScence :
	public Scence
{
	Map* tilemap;

	NumberThree* three;
	Curtain* curtain;

	Vector2 option, arrow; 

	LPSPRITE Option, Arrow;

	int instance;

	std::vector<LPGAMEOBJECT> earseobjects;
	std::vector <LPGAMEOBJECT> objects;
	std::vector<UIObject*> UIElement;

public:
	IntroScence();
	IntroScence(std::string id, std::string mappath, std::string filepath);
	~IntroScence();


	virtual void Load();

	virtual void Update(DWORD dt);

	virtual void Render();

	virtual void Unload();

	void addtoScenceManager();

	Camera* getCamera();

	void AddObject(LPGAMEOBJECT object) { objects.push_back(object); }

	void DeleteObject(LPGAMEOBJECT object) { earseobjects.push_back(object); }

	void PushObjectList(LPGAMEOBJECT object) { objects.push_back(object); }

	void AddUI(UIObject* UI) { UIElement.push_back(UI); }

};
class IntroKeyHandler :public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	IntroKeyHandler(Scence* s) : ScenceKeyHandler(s) {};
};
