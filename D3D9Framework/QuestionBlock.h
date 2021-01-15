#ifndef __QUESTIONBLOCK_H__
#define __QUESTIONBLOCK_H__

#include "GameObject.h"
#include "Camera.h"

#define BOUNCE_VEL	24.0f / 50.0f
#define BOUNCE_TIME	50

enum class Item
{
	PSwitch,
	RedShroom,
	RaccoonLeaf,
	FireFlower,
	GreenShroom,
	Coin
};

class QuestionBlock :
	public GameObject
{
	//in block object config
	int Quantity;

	Item InBlockItem;
	
	//question block boucing state
	bool Deflected;

	bool isBounce;

	int BounceState;

	DWORD Start_Bounce_Time;

	//Vector2 relativePosition; 

public:
	QuestionBlock();

	~QuestionBlock();

	void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny);

	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

	void Render(Camera* camera);

	virtual void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetInBlockItem(Item inblockitem);
	Item GetInBlockItem();

	void SetQuantity(int quantity);
	int GetQuantity();

	void SetDeflected(bool isdeflected);
	bool GetDeflected(); 

	void PopOutItem();

};

#endif // !__QUESTIONBLOCK_H__
