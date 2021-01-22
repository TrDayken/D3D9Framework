#include "Pipe.h"
#include "SpriteManager.h"

Pipe::Pipe()
{
	AddAnimation();

	dest_x = -1; 

	dest_y = -1;

	this->ColTag = Collision2DTag::FourSide ;

	this->EntityTag = Tag::pipe;

	this->setRenderOrder(4);
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

	RenderBoundingBox(camera);
}

void Pipe::setDes_x(float x)
{
	this->dest_x = x;
}

float Pipe::getDes_x()
{
	return this->dest_x;
}

void Pipe::setDes_y(float y)
{
	this->dest_y = y;
}

float Pipe::getDes_y()
{
	return this->dest_y;
}

void Pipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = this->Position.x; 
	t = this->Position.y; 
	r = this->Position.x + width;
	b = this->Position.y + height;
}

void Pipe::OnOverLap(GameObject* obj)
{
}
