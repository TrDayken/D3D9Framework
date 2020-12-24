#ifndef __UIOBJECT_H__
#define __UIOBJECT_H__

#include <unordered_map>

#include "SpriteManager.h"
#include "AnimationManager.h"
#include "Textures.h"

class UIObject
{
protected:
	Vector2 StaticPosition; 

	DWORD dt; 

	std::unordered_map<std::string, LPANIMATION> animation_set; 

public:
	UIObject(); 
	~UIObject(); 

	void setStaticPosition(Vector2 position); 
	Vector2 getStaticPosition(); 

	void AddAnimation(std::string name, LPANIMATION animation);

	virtual void Update(DWORD dt); 

	virtual void Render(); 
};

typedef UIObject* LPUIOBJECT;
#endif