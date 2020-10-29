#ifndef __ANIMATIONMANAGER_H__
#define __ANIMATIONMANAGER_H__

#include <d3dx9.h>
#include <unordered_map>
#include <string>

#include "Animation.h"
class AnimationManager
{
	static AnimationManager* _instance;

	std::unordered_map <std::string, LPANIMATION> animationDatabase;

public:
	void AddAnimation(std::string id, LPANIMATION animation);
	LPANIMATION GetAnimation(std::string id);
	void Clear();

	void AddAnimationUsingXML(const char* FilePath);

	static AnimationManager* GetInstance();
};

#endif