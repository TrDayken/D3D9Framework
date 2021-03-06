#include "Map.h"
#include "InvisibleBrick.h"
#include "GhostPlatform.h"
#include "QuestionBlock.h"
#include "Brick.h"
#include "Coin.h"
#include "WiggleTree.h"
#include "Node.h"
#include "NodeMap.h"
#include "EndGameReward.h"
#include "ScenceManager.h"
#include "Pipe.h"
#include "Goomba.h"
#include "Koopa.h"
#include "RedVenus.h"
#include "FakeGoldenBlock.h"
#include "WarpEntrance.h"
#include "RedGoomba.h"
#include "GreenPiranha.h"
#include "GreenVenus.h"
#include "MapScence.h"
#include "NodeVisual.h"
#include "FallingPlatform.h"
#include "GreenKoopa.h"
#include "BoomerangBrother.h"
#include "DeathBox.h"

Map::Map()
{
}

Map::~Map()
{
	Unload();
}

void Map::AddTileSet(LPTILESET tileset)
{
	this->tilesets = tileset;
}

void Map::AddLayer(LPLAYER layer)
{
	this->layers.push_back(layer);
}

void Map::AddObject(TiXmlElement* RootElement)
{
	for (TiXmlElement* TMXObjectsgroup = RootElement->FirstChildElement("objectgroup"); TMXObjectsgroup != NULL; TMXObjectsgroup = TMXObjectsgroup->NextSiblingElement("objectgroup"))
	{
		NodeMap* nodemap = new NodeMap();

		for (TiXmlElement* TMXObject = TMXObjectsgroup->FirstChildElement("object"); TMXObject != NULL; TMXObject = TMXObject->NextSiblingElement("object"))
		{
			int id;
			float x, y, width, height;
			//LPGAMEOBJECT object{};
			std::string name = TMXObjectsgroup->Attribute("name");
			if (name == "Solid")
			{
				InvisibleBrick* invisiblebrick = new InvisibleBrick();

				TMXObject->QueryIntAttribute("id", &id);

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				TMXObject->QueryFloatAttribute("width", &width);
				TMXObject->QueryFloatAttribute("height", &height);

				invisiblebrick->setID(id);
				invisiblebrick->setX(x);
				invisiblebrick->setY(y);
				invisiblebrick->setWidth(width);
				invisiblebrick->setHeight(height);

				ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(invisiblebrick);
				//object = new InvisibleBrick();
			}
			else if (name == "Ghost")
			{
				GhostPlatform* ghostplatform = new GhostPlatform();

				TMXObject->QueryIntAttribute("id", &id);

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				TMXObject->QueryFloatAttribute("width", &width);
				TMXObject->QueryFloatAttribute("height", &height);

				ghostplatform->setID(id);
				ghostplatform->setX(x);
				ghostplatform->setY(y);
				ghostplatform->setWidth(width);
				ghostplatform->setHeight(height);

				ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(ghostplatform);
			}
			else if (name == "Enemies")
			{
				GameObject* enemy = NULL;
				std::string enemyname, enemytype;

				TMXObject->QueryIntAttribute("id", &id);

				enemyname = TMXObject->Attribute("name");
				enemytype = TMXObject->Attribute("type");
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);

				if (enemyname == "goomba")
				{
					if (enemytype == "basic")
						enemy = new Goomba();
					else if(enemytype == "red-para")
						enemy = new RedGoomba();
				}
				else if (enemyname == "koopa")
				{
					if (enemytype == "red-para")
					{
						enemy = new Koopa();
						auto cast = dynamic_cast<Koopa*>(enemy);

						cast->SetState(KoopaState::fly);
					}
					else if (enemytype == "red")
					{
						enemy = new Koopa();
						auto cast = dynamic_cast<Koopa*>(enemy);

						cast->SetState(KoopaState::walking);
					}
					else if (enemytype == "green-para")
					{
						enemy = new GreenKoopa();
						auto cast = dynamic_cast<GreenKoopa*>(enemy);

						cast->SetState(KoopaState::fly);
					}
					else if (enemytype == "green")
					{
						enemy = new GreenKoopa();
						auto cast = dynamic_cast<GreenKoopa*>(enemy);

						cast->SetState(KoopaState::walking);
					}
				}
				else if (enemyname == "venus-fire-trap")
				{
					if (enemytype == "green")
						enemy = new GreenVenus();
					else if (enemytype == "red")
						enemy = new RedVenus();
				}
				else if (enemyname == "piranha-plant")
				{
					enemy = new GreenPiranha();
				}
				else if (enemyname == "boomerang-brother")
				{
					enemy = new BoomerangBrother();
				}
				else
					continue;

				enemy->setID(id);

				enemy->setX(x);
				enemy->setY(y);

				ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(enemy);
			}
			else if (name == "Items")
			{

				std::string name = TMXObject->Attribute("name");
				GameObject* obj = NULL;

				if (name == "coin")
					obj = new Coin();
				else if (name == "reward")
					obj = new EndGameReward();

				TMXObject->QueryIntAttribute("id", &id);

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);

				obj->setID(id);

				obj->setX(x);
				obj->setY(y);

				ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(obj);
			}
			else if (name == "QuestionBlocks")
			{
				QuestionBlock* questionblock = new QuestionBlock();
				int quantity = 0;
				std::string blockname;

				TMXObject->QueryIntAttribute("id", &id);

				blockname = TMXObject->Attribute("name");
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				TMXObject->QueryIntAttribute("type", &quantity);

				if (blockname == "bleaf")
				{
					questionblock->SetInBlockItem(Item::RaccoonLeaf);
				}
				else if (blockname == "bcoin")
				{
					questionblock->SetInBlockItem(Item::Coin);
				}
				else if (blockname == "bmushroom")
				{
					questionblock->SetInBlockItem(Item::RedShroom);
				}
				else if (blockname == "bswitch")
				{
					questionblock = new FakeGoldenBlock();
					questionblock->SetInBlockItem(Item::PSwitch);
				}
				else if (blockname == "fcoin")
				{
					questionblock = new FakeGoldenBlock();
					questionblock->SetInBlockItem(Item::Coin);
				}
				else if (blockname == "fleaf")
				{
					questionblock = new FakeGoldenBlock();
					questionblock->SetInBlockItem(Item::RaccoonLeaf);
				}
				else if (blockname == "f1up-mushroom")
				{
					questionblock = new FakeGoldenBlock();
					questionblock->SetInBlockItem(Item::GreenShroom);
				}

				questionblock->setID(id);
				questionblock->SetQuantity(quantity);
				questionblock->setX(x);
				questionblock->setY(y);

				if (quantity <= 0)
					questionblock->SetDeflected(true);

				ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(questionblock);
			}
			else if (name == "Bricks")
			{
				Brick* brick = new Brick();

				TMXObject->QueryIntAttribute("id", &id);

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);

				brick->setID(id);
				brick->setX(x);
				brick->setY(y);

				ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(brick);
			}
			else if (name == "Pipes")
			{
				Pipe* pipe = new Pipe();

				std::string pipetype;
				int width, height;

				float desx = -1;
				float desy = -1;

				bool isstatic = false, isfollow = false, scrollx = false, scrolly = false;
				float lock_x = 0, lock_y = 0;

				int caml = 0, camt = 0, camr = 0, camb = 0;

				TMXObject->QueryIntAttribute("id", &id);

				pipetype = TMXObject->Attribute("type");
				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				TMXObject->QueryIntAttribute("width", &width);
				TMXObject->QueryIntAttribute("height", &height);



				if (pipetype == "green-up")
					pipe->SetPipeDirection(PipeDirection::Up);
				else if (pipetype == "green-down")
					pipe->SetPipeDirection(PipeDirection::Down);
				else if (pipetype == "green-vertical")
					pipe->SetPipeDirection(PipeDirection::Vertical);


				TiXmlElement* TMXproperties = TMXObject->FirstChildElement("properties");

				if (TMXproperties != nullptr)
				{
					for (TiXmlElement* TMXproperty = TMXproperties->FirstChildElement("property"); TMXproperty != NULL; TMXproperty = TMXproperty->NextSiblingElement("property"))
					{


						std::string propertyname = TMXproperty->Attribute("name");

						if (propertyname == "dest-x")
						{
							TMXproperty->QueryFloatAttribute("value", &desx);
						}
						if (propertyname == "dest-y")
						{
							TMXproperty->QueryFloatAttribute("value", &desy);
						}


						if (propertyname == "isstatic")
						{
							TMXproperty->QueryBoolAttribute("value", &isstatic);
						}
						if (propertyname == "isfollow")
						{
							TMXproperty->QueryBoolAttribute("value", &isfollow);
						}
						if (propertyname == "scrollx")
						{
							TMXproperty->QueryBoolAttribute("value", &scrollx);
						}
						if (propertyname == "scrolly")
						{
							TMXproperty->QueryBoolAttribute("value", &scrolly);
						}
						if (propertyname == "lock-x")
						{
							TMXproperty->QueryFloatAttribute("value", &lock_x);
						}
						if (propertyname == "lock-y")
						{
							TMXproperty->QueryFloatAttribute("value", &lock_y);
						}


						if (propertyname == "caml")
						{
							TMXproperty->QueryIntAttribute("value", &caml);
						}
						if (propertyname == "camt")
						{
							TMXproperty->QueryIntAttribute("value", &camt);
						}
						if (propertyname == "camr")
						{
							TMXproperty->QueryIntAttribute("value", &camr);
						}
						if (propertyname == "camb")
						{
							TMXproperty->QueryIntAttribute("value", &camb);
						}
					}
	
				}

				pipe->setCamProp(camt, caml, camr, camb);

				pipe->setIsfollow(isfollow);
				pipe->setIsstatic(isstatic);
				pipe->setScrollx(scrollx);
				pipe->setScrolly(scrolly);
				pipe->setLockx(lock_x);
				pipe->setLocky(lock_y);

				pipe->setID(id);
				pipe->setDes_x(desx);
				pipe->setDes_y(desy);
				pipe->setX(x);
				pipe->setY(y);
				pipe->SetTile(width, height);

				ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(pipe);
			}
			else if (name == "MovingPlatforms")
			{
			FallingPlatform* platform = new FallingPlatform();

			TMXObject->QueryIntAttribute("id", &id);

			TMXObject->QueryFloatAttribute("x", &x);
			TMXObject->QueryFloatAttribute("y", &y);


			platform->setID(id);
			platform->setX(x);
			platform->setY(y);


			ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(platform);
			}
			else if (name == "Warp") 
			{
				WarpEntrance* entrance = new WarpEntrance();
				std::string dir; 

				TMXObject->QueryIntAttribute("id", &id);

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				TMXObject->QueryFloatAttribute("width", &width);
				TMXObject->QueryFloatAttribute("height", &height);

				dir = TMXObject->Attribute("type");

				if (dir == "up")
				{
					entrance->setWarpDirection(WarpDirection::up);
				}
				else if (dir == "down")
				{
					entrance->setWarpDirection(WarpDirection::down);
				}
				else if (dir == "right")
				{
					entrance->setWarpDirection(WarpDirection::right);
				}
				else if (dir == "left")
				{
					entrance->setWarpDirection(WarpDirection::left);
				}

				entrance->setID(id);
				entrance->setX(x);
				entrance->setY(y);
				entrance->setWidth(width);
				entrance->setHeight(height);

				ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(entrance);
			}
			else if (name == "DeadBox")
			{
			DeathBox* invisiblebrick = new DeathBox();

			TMXObject->QueryIntAttribute("id", &id);

			TMXObject->QueryFloatAttribute("x", &x);
			TMXObject->QueryFloatAttribute("y", &y);
			TMXObject->QueryFloatAttribute("width", &width);
			TMXObject->QueryFloatAttribute("height", &height);

			invisiblebrick->setID(id);
			invisiblebrick->setX(x);
			invisiblebrick->setY(y);
			invisiblebrick->setWidth(width);
			invisiblebrick->setHeight(height);

			ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(invisiblebrick);
 }
			else if (name == "WorldGraph")
			{
				std::string objectname;
				int nodename = 0;
				std::vector<std::string> adlist;
				std::vector<std::string> weight;
				std::string scence;

				TMXObject->QueryIntAttribute("id", &id);

				objectname = TMXObject->Attribute("name");
				auto nodetype = TMXObject->Attribute("type");

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				//auto type = split(TMXObject->Attribute("type"));

				TiXmlElement* TMXproperties = TMXObject->FirstChildElement("properties");

				if (TMXproperties != nullptr)
				{
					for (TiXmlElement* TMXproperty = TMXproperties->FirstChildElement("property"); TMXproperty != NULL; TMXproperty = TMXproperty->NextSiblingElement("property"))
					{
						std::string propertyname = TMXproperty->Attribute("name");

						if (propertyname == "adjacent_list")
						{
							adlist = split(TMXproperty->Attribute("value"), ",");
						}
						else if (propertyname == "adjacent_weight")
						{
							weight = split(TMXproperty->Attribute("value"), ",");
						}
						else if (propertyname == "node_id")
						{
							nodename = std::stoi(TMXproperty->Attribute("value"));
						}
						else if (propertyname == "scene")
						{
							scence = TMXproperty->Attribute("value");
						}
					}
				}

				if(nodetype != NULL)
				if (nodetype != "")
				{
					auto num = split(nodetype, "-");

					if (num.at(0) == "num")
					{
						NodeVisual* visual = new NodeVisual();

						visual->setPosition(x, y);
						visual->SetNumber(stoi(num.at(1)));


						ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(visual);
					}
					else if (num.at(0) == "bonus")
					{
						if (num.at(1) == "slot")
						{
							NodeVisual* visual = new NodeVisual();

							visual->setPosition(x, y);
							visual->SetNumber(7);

							ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(visual);
						}
					}

				}

				Node* node = new Node();

				node->setNodeID(nodename);
				node->setPosition(Vector2(x, y));
				node->setScence(scence);

				auto adjacentlist = node->getAdjacentList();

				for (int i = 0; i < adlist.size(); i++)
				{
					auto id = std::stoi(adlist[i]);

					Edge edge;
					edge.nodeID = id;

					NextNode next = NextNode::none;

					if (weight[i] == "l") next = NextNode::left;
					else if (weight[i] == "r") next = NextNode::right;
					else if (weight[i] == "u") next = NextNode::up;
					else if (weight[i] == "d") next = NextNode::down;

					edge.direction = next; 

					adjacentlist->push_back(edge);
				}

				nodemap->InsertNode(node);

				//if (type.at(0).compare("num") == 0)
				//{
				//	//add gate
				//}
				//else if (type.at(0).compare("bonus") == 0)
				//{
				//	if (type.at(1).compare("slot") == 0)
				//	{
				//		//add another gate
				//	}
				//}
			}
			else if (name == "AnimatedBG")
			{
				WiggleTree* tree = new WiggleTree();

				TMXObject->QueryIntAttribute("id", &id);

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);

				tree->setX(x);
				tree->setY(y);

				ScenceManager::GetInstance()->getCurrentScence()->PushObjectList(tree);
			}
			else
			{
				continue;
			}


		}

		Scence* scence = ScenceManager::GetInstance()->getCurrentScence();
		if (scence != NULL)
		{
			auto mapscence = dynamic_cast<MapScence*>(scence);
			if (mapscence != NULL)
			{
				mapscence->GetPlayer()->setMap(nodemap);
			}
		}
	}
}

void Map::LoadMapfromTMX(const char* FilePath, const char* Path)
{
	TiXmlDocument TMXdoc(FilePath);

	if (TMXdoc.LoadFile())
	{
		TiXmlElement* root = TMXdoc.RootElement();

		root->QueryIntAttribute("width", &this->width);
		root->QueryIntAttribute("height", &this->height);
		root->QueryIntAttribute("tilewidth", &this->tilewidth);
		root->QueryIntAttribute("tileheight", &this->tileheight);

		for (TiXmlElement* TMXtileset = root->FirstChildElement("tileset"); TMXtileset != NULL; TMXtileset = TMXtileset->NextSiblingElement("tileset"))
		{
			LPTILESET tileset = new TileSet(TMXtileset, Path);
			this->AddTileSet(tileset);

			//DebugOut(L"[INFO] load success tileset: %", tileset->getFirstgid());
		}

		for (TiXmlElement* TMXlayer = root->FirstChildElement("layer"); TMXlayer != NULL; TMXlayer = TMXlayer->NextSiblingElement("layer"))
		{
			LPLAYER layer = new Layer( TMXlayer);
			this->AddLayer(layer);
		}

		this->AddObject(root);

		DebugOut(L"[INFO] map load successful \n");
	}
	else
	{
		DebugOut(L"[ERROR] failed to load map \n");
	}

}

void Map::Update(DWORD dt)
{
}

//this funtion is ugly and may be refine 
// note: multilayer cast error need to be fixed
void Map::Render(Camera* camera)
{
	//[NAIVE APPROACH]
	//for (int i = 0; i < width; i++)
	//{
	//	for (int j = 0; j < height; j++)
	//	{
	//		int x = i * tilewidth;
	//		int y = j * tileheight;
	//		for (LPLAYER layer : layers)
	//		{
	//			int id = layer->GetTileID(i,j);

	//			if (id != 0)
	//				tilesets->Draw(id - 1, x, y);
	//				//this->GetTilesetbyTileID(id - 1)->Draw(id, x, y);
	//		}
	//	}
	//}

	int col = camera->getCameraPositionX() / tilewidth;
	int row = camera->getCameraPositionY() / tileheight;

	if (col > 0) col--;
	if (row > 0) row--;

	float camsizeX = camera->getCameraWidth() / tilewidth;
	float camsizey = camera->getCameraHeight() / tileheight;

	for (int i = col; i < camsizeX + col + 2; i++)
	{
		for (int j = row; j < camsizey + row + 2; j++)
		{
			int x = i * tilewidth - camera->getCameraPositionX();
			int y = j * tileheight - camera->getCameraPositionY();

			for (LPLAYER layer : layers)
			{
				if (layer->getVisible() == true)
				{
					int id = layer->GetTileID(i % width, j % height);
					if (id != 0)
					{
						tilesets->Draw(id - 1, x, y);
					}
				}
			}
		}
	}
}

void Map::Unload()
{
	layers.clear();
}

//use this to set specific layers as object
void Map::setObjectonLayer(std::vector<LPGAMEOBJECT> *listobject, std::string layername)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int x = i * tilewidth;
			int y = j * tileheight;
			for (LPLAYER layer : layers)
			{
				if (layer->getName() == layername)
				{
					int id = layer->GetTileID(i, j);

					if (id != 0)
					{
						GameObject* obj = NULL;

						obj = new InvisibleBrick();

						obj->setPosition(x, y);

						float z, u;
						obj->getPosition(z, u);
						//DebugOut(L"[INFO] invisible object x:%f y:%f \n", z, u);

						listobject->push_back(obj);
					}
				}
			}
		}
	}
}

float Map::getMapHeight()
{
	return this->height*this->tileheight;
}

float Map::getMapWidth()
{
	return this->width * this->tilewidth;
}

LPTILESET Map::GetTilesetbyTileID(int ID)
{
	return tilesets;
}
