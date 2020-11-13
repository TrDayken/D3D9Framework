#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <d3dx9.h>
#include <d3dx9math.h>
#include <string>

#include "Game.h" 
#include "Global_Variable.h"

class Sprite
{
	std::string id; 
	
	RECT spriteRect;
	int xPivot;
	int yPivot;
	int SpriteWidth;
	int SpriteHeight;

	Vector2 position;
	float rotation;
	Vector2 scale;
	Vector2 origin;
	Vector2 anchorPoint;

	LPDIRECT3DTEXTURE9 texture;

public:
	Sprite(int id, int left, int top, int right, int bottom,int xpivot, int ypivot, LPDIRECT3DTEXTURE9 texture);
	Sprite(std::string id, RECT rect, int xpivot, int ypivot, LPDIRECT3DTEXTURE9 texture);

	~Sprite();

	void SetScale(Vector2 Scale);

	void Draw();
	void Draw(int x , int y , int direction = 1 , int flipy = 1, int alpha = 255);

	Vector2 getPosition();
	void setPosition(Vector2 position);

	float getRotation();
	void setRotationbyRadian(float Radian);
	void setRotationbyDegree(float Degree);

	Vector2 getScale();
	void setScale(Vector2 scale);
	void setScale(float scaleX, float scaleY);
	void flipX();
	void flipY();


};

typedef Sprite* LPSPRITE;

#endif