#include "Animation.h"

Animation::Animation(int defaultTime)
{
	this->defaultTime = defaultTime;
	this->multiplier = 1;
}

void Animation::AddFrame(std::string spriteID, DWORD Frametime)
{
	int t = Frametime;
	if (Frametime == 0) t = this->defaultTime;
	
	LPSPRITE sprite = SpriteManager::GetInstance()->GetSprite(spriteID);

	if (sprite == NULL)
	{
		//DebugOut(L"[ERROR] Sprite ID %d cannot find \n", spriteID);
		OutputDebugStringW(ToLPCWSTR("[ERROR] cannot find sprite ID: " + spriteID + "\n"));
	}

	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::setMultiplier(int multiplier)
{
	this->multiplier = multiplier;
}

void Animation::Render(float x, float y, Vector2 scale, int direction , int flipy , int alpha)
{
	DWORD now = GetTickCount();

	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD time = frames[currentFrame]->getTime();
		if (now - lastFrameTime > time/ multiplier)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size())
				currentFrame = 0;
		}

		frames[currentFrame]->GetSprite()->Draw(x, y, scale, direction, flipy, alpha);
	}
}

