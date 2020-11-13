#ifndef __PLAYSCENCE_H__
#define __PLAYSCENCE_H__

#include "Scence.h"
#include "Mario.h"
#include "Map.h"
#include "Camera.h"
#include "ScenceManager.h"
#include "Goomba.h"

class PlayScence : public Scence
{
protected:
	Mario* mario;
	Map* tilemap;


	std::vector<LPGAMEOBJECT> earseobjects;
	std::vector <LPGAMEOBJECT> objects;

public:
	PlayScence();
	PlayScence(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void AddObject(LPGAMEOBJECT object) { objects.push_back(object); }
	void DeleteObject(LPGAMEOBJECT object) { earseobjects.push_back(object); }
	Mario* GetPlayer() { return mario; }
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
