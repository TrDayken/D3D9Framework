#include "MapMario.h"
#include "AnimationManager.h"
#include "ScenceManager.h"

void MapMario::LoadAnimation()
{
	auto animations = AnimationManager::GetInstance();

	AddAnimation("SmallMario", animations->GetAnimation("ani-small-mario-map"));
	AddAnimation("BigMario", animations->GetAnimation("ani-big-mario-map"));
	AddAnimation("RaccoonMario", animations->GetAnimation("ani-raccoon-mario-map"));
	AddAnimation("FireMario", animations->GetAnimation("ani-fire-mario-map"));
}

MapMario::MapMario()
{
	LoadAnimation();

	ismovingx = ismovingy = false;

	currentNode = 0;
}

MapMario::~MapMario()
{
	
}

void MapMario::Update(DWORD dt, std::vector<LPGAMEOBJECT>* collision_objects)
{
	//this->Position = map->getNode(currentNode)->getPosition();

	if (ismovingx || ismovingy)
	{
		//if (this->Position.x < des.x)
		//	this->Position.x += MARIO_SPEED * dt

		if (distance.x > 0)
		{
			if (this->Position.x < this->des.x)
			{
				RelativePosition.x += MARIO_SPEED * dt;
				distance.x -= MARIO_SPEED * dt;
			}
			else
			{
				RelativePosition.x -= MARIO_SPEED * dt;
				distance.x -= MARIO_SPEED * dt;
			}
		}
		else
		{
			distance.x = 0;
			RelativePosition.x = 0;
			this->Position.x = des.x;
			ismovingx = false;
		}

		if (distance.y > 0)
		{
			if (this->Position.y < this->des.y)
			{
				RelativePosition.y += MARIO_SPEED * dt;
				distance.y -= MARIO_SPEED * dt;
			}
			else
			{
				RelativePosition.y -= MARIO_SPEED * dt;
				distance.y -= MARIO_SPEED * dt;
			}
		}
		else
		{
			distance.y = 0;
			RelativePosition.y = 0;
			this->Position.y = des.y;
			ismovingy= false;
		}

	}
}

void MapMario::setMap(NodeMap* map)
{
	this->map = map;
}

NodeMap* MapMario::getMap()
{
	return this->map;
}

void MapMario::Render(Camera* camera)
{
	GameObject::Render(camera);

	animation_set["SmallMario"]->Render(RenderPosition.x, RenderPosition.y);
}

void MapMario::OnKeyDown(int KeyCode)
{
	//DIK_A: SELECT
	//DIK_UP,_DOWN_LEFT_RIGHT: MOVE TO NODE;

	//mario moving dont accept
	if (this->ismovingx || this->ismovingy) return;

	auto currentnode = map->getNode(this->currentNode);

	if (KeyCode == DIK_A)
	{
		if (currentnode->getScence() != "")
			ScenceManager::GetInstance()->SwitchScence(currentnode->getScence());
	}	


	int acceptedKey;
	for (auto adj : *currentnode->getAdjacentList())
	{
		switch (adj.direction)
		{
		case NextNode::left: acceptedKey = (DIK_LEFT); break;
		case NextNode::right: acceptedKey = (DIK_RIGHT); break;
		case NextNode::up: acceptedKey = (DIK_UP); break;
		case NextNode::down: acceptedKey = (DIK_DOWN); break;
		}

		if (KeyCode == acceptedKey)
		{
			auto adjNode = map->getNode(adj.nodeID);
			if (adjNode)
			{
				this->predes = currentnode->getPosition();

				currentNode = adj.nodeID;
				des = adjNode->getPosition();

				distance.x = abs(this->Position.x - des.x);
				if (distance.x > 0)
					ismovingx = true;
				distance.y = abs(this->Position.y - des.y);
				if (distance.y > 0)
					ismovingy = true;
			}
			break;
		}
	}
}
