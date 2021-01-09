#include "Pipe.h"
#include "SpriteManager.h"

Pipe::Pipe()
{
	AddAnimation();
}

void Pipe::AddAnimation()
{
	auto sprite = SpriteManager::GetInstance();

	headTile = sprite->GetSprite("spr-pipe-head");
	bodyTile = sprite->GetSprite("spr-pipe-body");
}

void Pipe::SetTile(int x, int y)
{
	this->tile_X = x / TILE_SIZE;
	this->tile_Y = y / TILE_SIZE;
	this->width = tile_X * TILE_SIZE;
	this->height = tile_Y * TILE_SIZE;

	rendervector.clear();

	switch (dir)
	{
	case PipeDirection::Up:
		for (int i = 0; i < tile_Y; i++)
		{
			if (i == 0)
				rendervector.push_back(headTile);
			else
				rendervector.push_back(bodyTile);
		}

		flipy = 1;
		break;
	case PipeDirection::Down:
		for (int i = 0; i < tile_Y; i++)
		{
			if (i == (tile_Y - 1))
				rendervector.push_back(headTile);
			else
				rendervector.push_back(bodyTile);
		}

		flipy = -1;
		break;
	case PipeDirection::Vertical:
		for (int i = 0; i < tile_Y; i++)
		{
			rendervector.push_back(bodyTile);
		}

		flipy = 1; 
		break;
	default:
		break;
	}
}

void Pipe::SetPipeDirection(PipeDirection dir)
{
	this->dir = dir; 
}

void Pipe::Render(Camera* camera)
{
	GameObject::Render(camera);

	for (int i = 0; i < rendervector.size(); i++)
	{
		rendervector[i]->Draw(this->RenderPosition.x, this->RenderPosition.y + i * TILE_SIZE,Vector2(1.0 , flipy)); 
	}

	//headTile->Draw(this->RenderPosition.x, this->RenderPosition.y);

	//RenderBoundingBox(camera);
}

void Pipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x; 
	t = this->Position.y; 
	r = this->Position.x + width;
	b = this->Position.y + height;
}
