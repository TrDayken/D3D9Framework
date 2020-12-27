#ifndef __PLAYSCENCE_H__
#define __PLAYSCENCE_H__

#include "Scence.h"
#include "Mario.h"
#include "Map.h"
#include "Camera.h"
#include "ScenceManager.h"
#include "Goomba.h"
#include "UIObject.h"
#include "HUD.h"

class PlayScence : public Scence
{
protected:
	Mario* mario;
	Map* tilemap;

	HUD* hud; 

	std::vector<LPGAMEOBJECT> earseobjects;
	std::vector <LPGAMEOBJECT> objects;
	std::vector<UIObject*> UIElement;

public:
	PlayScence();
	PlayScence(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	//spawnobject(obj)
	void AddObject(LPGAMEOBJECT object) { objects.push_back(object); }

	void DeleteObject(LPGAMEOBJECT object) { earseobjects.push_back(object); }

	void AddUI(UIObject* UI) { UIElement.push_back(UI); };

	Mario* GetPlayer() { return mario; }

	//int getPmetter() { return this->mario->getPmetter(); }

	void addtoScenceManager();

	Camera* getCamera();
};

class PlayScenceKeyHandler : public ScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	PlayScenceKeyHandler(Scence* s) : ScenceKeyHandler(s) {};
};

#endif
