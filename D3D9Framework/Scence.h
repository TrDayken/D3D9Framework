#ifndef __SCENCE_H__
#define	__SCENCE_H__

#include <d3dx9.h>

#include "KeyEventHandler.h"
#include "GameObject.h"	
#include "UIObject.h"

class Scence
{
protected:
	KeyEventHandler* key_handler;

	std::string id;
	std::string sceneFilePath;
	std::string mapPath;
	Camera* camera;

	bool unload;

public:
	Scence();
	Scence(std::string id,std::string mappath, std::string filePath);

	KeyEventHandler* GetKeyEventHandler() { return key_handler; }

	virtual Camera* getCamera() { return this->camera; }
	virtual void AddObject(LPGAMEOBJECT object) = 0;
	virtual void DeleteObject(LPGAMEOBJECT object) = 0;
	virtual void PushObjectList(LPGAMEOBJECT object) = 0;
	virtual void AddUI(UIObject* UI) = 0; 
	//virtual void DeleteUI(UIObject* UI) {};
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