#ifndef __SCENCE_H__
#define	__SCENCE_H__

#include <d3dx9.h>

#include "KeyEventHandler.h"
#include "GameObject.h"	

class Scence
{
protected:
	KeyEventHandler* key_handler;
	int id;
	LPCWSTR sceneFilePath;
	Camera* camera;

public:
	Scence();
	Scence(int id, LPCWSTR filePath);

	KeyEventHandler* GetKeyEventHandler() { return key_handler; }

	virtual Camera* getCamera() { return this->camera; }
	virtual void addobject(LPGAMEOBJECT object) = 0;
	virtual void delobject(LPGAMEOBJECT object) = 0;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef Scence* LPSCENCE;


class ScenceKeyHandler : public KeyEventHandler
{
protected:
	Scence* scence;

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	ScenceKeyHandler(Scence* s) :KeyEventHandler() { scence = s; }
};

#endif