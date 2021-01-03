#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <d3dx9.h>
#include <vector>

#include "Utils.h"
#include "Sprite.h"
#include "SpriteManager.h"

struct AnimationFrame
{
private:
	LPSPRITE sprite;
	DWORD time;
public:
	AnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }

	void setTime(DWORD time) { this->time = time; }
	DWORD getTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};
	
typedef AnimationFrame* LPANIMATION_FRAME;

class Animation
{
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	float multiplier;
	std::vector<LPANIMATION_FRAME> frames;

public:
	Animation(int defaultTime = 100);

	void AddFrame(std::string spriteID, DWORD Frametime = 0);
	
	void setMultiplier(int multiplier = 1);

	void Update();
	void Render(float x, float y, Vector2 scale = Vector2(1.0, 1.0) , int direction = 1, int flipy = 1, int alpha = 255);
};

typedef Animation* LPANIMATION;

#endif
