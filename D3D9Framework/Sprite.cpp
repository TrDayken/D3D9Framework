#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(int id, int left, int top, int right, int bottom, int xpivot, int ypivot, LPDIRECT3DTEXTURE9 texture)
{
	//this->id = id;
	this->spriteRect.left= left;
	this->spriteRect.top = top;
	this->spriteRect.right = right;
	this->spriteRect.bottom = bottom;
	this->texture = texture;
	this->xPivot = xpivot;
	this->yPivot = ypivot;
	this->SpriteWidth = abs(right - left);
	this->SpriteHeight = abs(bottom - top);

	this->origin = Vector2(0.5f, 0.5f);
	this->scale = Vector2(10.0f, 10.0f);
	this->rotation = 0.0f;

	this->position = Vector2(100, 100);
}

Sprite::Sprite(std::string id, RECT rect, int xpivot, int ypivot, LPDIRECT3DTEXTURE9 texture)
{
	this->id = id;
	this->spriteRect.left = rect.left;
	this->spriteRect.top = rect.top;
	this->spriteRect.right = rect.right;
	this->spriteRect.bottom = rect.bottom;
	this->texture = texture;

	this->xPivot = xpivot;
	this->yPivot = ypivot;

	this->SpriteWidth = abs(rect.right - rect.left);
	this->SpriteHeight = abs(rect.bottom - rect.top);

	this->origin = Vector2(0.5f, 0.5f);
	this->scale = Vector2(1.0f, 1.0f);
	this->rotation = 0.0f;
	this->position = Vector2(100, 100);
}

Sprite::~Sprite()
{
}


void Sprite::SetScale(Vector2 Scale)
{
	this->scale = Scale;
}

void Sprite::Draw()
{
	Game::GetInstance()->Draw(position.x, position.y, texture, spriteRect, scale, rotation, SpriteWidth * origin.x, SpriteHeight * (1 - origin.y), xPivot, yPivot, 255);
}

void Sprite::Draw(int x, int y, Vector2 scale, int direction, int flipy, int alpha)
{
	Game::GetInstance()->Draw(x, y, texture, spriteRect, Vector2(this->scale.x * scale.x, this->scale.y * scale.y) , rotation, SpriteWidth * origin.x, SpriteHeight * (1 - origin.y), xPivot, yPivot, direction, flipy, alpha);
}


Vector2 Sprite::getPosition()
{
	return this->position;
} 

void Sprite::setPosition(Vector2 position)
{
	this->position = position;
}

float Sprite::getRotation()
{
	return this->rotation;
}

void Sprite::setRotationbyRadian(float rotation)
{
	this->rotation = rotation;
}

void Sprite::setRotationbyDegree(float Degree)
{
	this->rotation = D3DXToRadian(Degree);
}

Vector2 Sprite::getScale()
{
	return this->scale;
}

void Sprite::setScale(Vector2 scale)
{
	this->scale = scale;
}

void Sprite::setScale(float scaleX, float scaleY)
{
	this->scale = Vector2(scaleX, scaleY);
}

void Sprite::flipX()
{
	setScale(-scale.x, scale.y);
}

void Sprite::flipY()
{
	setScale(scale.x, -scale.y);
}

int Sprite::getSpriteWidth()
{
	return this->SpriteWidth;
}

int Sprite::getSpriteHeight()
{
	return this->SpriteHeight;
}
