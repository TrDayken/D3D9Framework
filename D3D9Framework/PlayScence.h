#ifndef __PLAYSCENCE_H__
#define __PLAYSCENCE_H__

#include "Scence.h"
#include "Mario.h"
#include "Map.h"
class PlayScence : public Scence
{
protected:
	Mario* player;
	Map* tilemap;


	std::vector <LPGAMEOBJECT> objects;

public:
	PlayScence();
	PlayScence(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	Mario* GetPlayer() { return player; }
};

class PlayScenceKeyHandler : public ScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};

	PlayScenceKeyHandler(Scence* s) : ScenceKeyHandler(s) {};
};

#endif
