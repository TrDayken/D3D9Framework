#pragma once

#include <d3dx9.h>
#include <vector>

#include "Sprite.h"

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
	std::vector<LPANIMATION_FRAME> frames;

public:
	Animation(int defaultTime = 100);

	void AddFrame(int spriteID, DWORD time = 0);
	
	void Render(float x, float y, int alpha = 255);
};

typedef Animation* LPANIMATION;

