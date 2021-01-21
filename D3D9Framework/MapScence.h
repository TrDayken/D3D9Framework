#pragma once

#include "Scence.h"
#include "MapMario.h"
#include "HUD.h"
#include "Map.h"

class MapScence :
	public Scence
{
	MapMario* mario;

	HUD* hud;

	Map* tilemap;

	std::vector<LPGAMEOBJECT> earseobjects;
	std::vector <LPGAMEOBJECT> objects;
	std::vector<UIObject*> UIElement;

public: 

	MapScence();
	MapScence(std::string id, std::string mappath, std::string filepath);
	~MapScence();

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

	MapMario* GetPlayer() { return mario; }
};

class MapScenceKeyHandler :public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	MapScenceKeyHandler(Scence* s) : ScenceKeyHandler(s) {};
};