#ifndef __QUESTIONBLOCK_H__
#define __QUESTIONBLOCK_H__

#include "GameObject.h"
#include "Camera.h"

enum class Item
{
	RedShroom,
	RaccoonLeaf,
	FireFlower,
	GreenShroom
};

class QuestionBlock :
	public GameObject
{
	//in block object config
	int Quantity;
	Item InBlockItem;
	
	//question block boucing state
	int Deflected;

public:
	QuestionBlock();
	~QuestionBlock();

	void OnCollisionEnter(LPGAMEOBJECT obj, int nx, int ny);

	//void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);

	void Render(Camera* camera);

	void LoadAnimation();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetInBlockItem(Item inblockitem);
	Item GetInBlockItem();

	void SetQuantity(int quantity);
	int GetQuantity();

};

#endif // !__QUESTIONBLOCK_H__
