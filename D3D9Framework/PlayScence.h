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
#include "Grid.h"

#define LAYER_SIZE 6
// 0 collectibles
// 1 block
// 2 entities
// 3 mario
// 4 pipe
// 5 fx

class PlayScence : public Scence
{
protected:
	Mario* mario;
	Map* tilemap;

	HUD* hud; 

	Grid* grid; 

	std::vector<LPGAMEOBJECT> earseobjects;
	std::vector <LPGAMEOBJECT> objects;

	std::vector<LPGAMEOBJECT> activegameobject;
	std::vector<UIObject*> UIElement;

	int boundl, boundt, boundr, boundb;

	bool isstatic, isfollow, scrollx, scrolly;

	float startx, starty;

	int jumpbound; 

public:
	PlayScence();
	PlayScence(std::string id, std::string mappath, std::string filepath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	Grid* getGrid();

	void setGrid(Grid* grid);

	//spawnobject(obj)
	//remake
	void AddObject(LPGAMEOBJECT object);

	//remake
	void DeleteObject(LPGAMEOBJECT object);

	void PushObjectList(LPGAMEOBJECT object) { objects.push_back(object); }

	void setStartBound(int l, int r, int t, int b);

	void setJumpBound(int j);

	void setStartConfig(float startx, float starty, bool isstatic, bool isfollow, bool scrollx, bool scrolly);

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
