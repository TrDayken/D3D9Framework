#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <d3dx9.h>
#include <vector>
#include <algorithm>

#include "SpriteManager.h"
#include "AnimationManager.h"
#include "Camera.h"
#include "Textures.h"

class GameObject;
typedef GameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

enum class Collision2DTag
{
	FourSide,
	Top,
	None
};

enum class Tag
{
	platform,
	plant,
	entrance,
	pipe,
	enemy,
	brick,
	player,
	projectile,
	enemyprojectile,
	shell,
	tail,
	questionblock,
	coin,
	mushroom,
	leaf,
	vanity,
	pswitch
};

class GameObject
{
protected:
	

	//object direction 1 = right , -1 = left
	int direction, flipy;

	// object position
	Vector2 Position;

	Vector2 Scale; 

	// object relative sprite position
	Vector2 RelativePosition;
	Vector2 RenderPosition;
	//dx = vx * dt; dy = vy * dt;
	float dx, dy;

	// object speed
	float vx, vy;

	// object width, height;
	float width, height;

	int state;

	Collision2DTag ColTag;

	bool isBeingHold = false;
	bool isHoldAble = false;

	DWORD dt;
	std::unordered_map<std::string,LPANIMATION> animation_set;

public: 
	Tag EntityTag;
	GameObject();
	~GameObject();
	//speed and position geter/seter
	void setPosition(float x, float y);
	void getPosition(float& x, float& y);
	
	void setRelativePosition(float x, float y);
	void getRelativePosition(float& x, float& y);

	void setSpeed(float vx, float vy);
	void GetSpeed(float& vx, float& vy);
	
	virtual void setIsBeingHold(bool isBeingHold);
	bool IsHoldAble();
	virtual void setIsHoldAble(bool ishold);

	virtual float getX();
	virtual void setX(float x);

	virtual float getY();
	virtual void setY(float y);

	virtual float getVx();
	virtual void setVx(float vx);

	virtual float getVy();
	virtual void setVy(float vy);

	virtual float getWidth();
	virtual void setWidth(float width);

	virtual float getHeight();
	virtual void setHeight(float height);

	virtual void setDirection(int direction);
	virtual int getDirection();

	virtual int getState();

	void RenderBoundingBox(Camera* camera);
	
	void AddAnimation(std::string name , LPANIMATION animation);
	//void setAnimationSet();
	//void CloneAnimation();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render(Camera* camera);
	virtual void SetState(int state) { this->state = state; }
	//virtual void LoadAnimation() = 0;

	virtual void OnOverLap(GameObject* object) {};
	bool IsOverLapped(GameObject* object);
	bool CheckOverlapped(float left, float top, float right, float bottom, float left1, float top1, float right1, float bottom1);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(std::vector<LPGAMEOBJECT>* coObjects, std::vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		std::vector<LPCOLLISIONEVENT>& coEvents,
		std::vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);
	void FilterCollisionX(std::vector<LPCOLLISIONEVENT>& coEvents,
		std::vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& nx, float& rdx);
	void FilterCollisionY(std::vector<LPCOLLISIONEVENT>& coEvents,
		std::vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_ty,
		float& ny, float& rdy);
	virtual void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny) {};
};

#endif