#include "Map.h"
#include "InvisibleBrick.h"
#include "GhostPlatform.h"
#include "QuestionBlock.h"
#include "Brick.h"
#include "Coin.h"
#include "ScenceManager.h"

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
		for (TiXmlElement* TMXObject = TMXObjectsgroup->FirstChildElement("object"); TMXObject != NULL; TMXObject = TMXObject->NextSiblingElement("object"))
		{

			float x, y, width, height;
			//LPGAMEOBJECT object{};
			std::string name = TMXObjectsgroup->Attribute("name");
			if (name == "Solid")
			{
				InvisibleBrick* invisiblebrick = new InvisibleBrick();

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				TMXObject->QueryFloatAttribute("width", &width);
				TMXObject->QueryFloatAttribute("height", &height);

				invisiblebrick->setX(x);
				invisiblebrick->setY(y);
				invisiblebrick->setWidth(width);
				invisiblebrick->setHeight(height);

				ScenceManager::GetInstance()->getCurrentScence()->AddObject(invisiblebrick);
				//object = new InvisibleBrick();
			}
			else if (name == "Ghost")
			{
				GhostPlatform* ghostplatform = new GhostPlatform();

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);
				TMXObject->QueryFloatAttribute("width", &width);
				TMXObject->QueryFloatAttribute("height", &height);

				ghostplatform->setX(x);
				ghostplatform->setY(y);
				ghostplatform->setWidth(width);
				ghostplatform->setHeight(height);

				ScenceManager::GetInstance()->getCurrentScence()->AddObject(ghostplatform);
			}
			else if (name == "Enemies")
			{
				continue;
			}
			else if (name == "Items")
			{
				Coin* coin = new Coin(); 

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);

				coin->setX(x);
				coin->setY(y);

				ScenceManager::GetInstance()->getCurrentScence()->AddObject(coin);
			}
			else if (name == "QuestionBlocks")
			{
				QuestionBlock* questionblock = new QuestionBlock();
				int quantity = 0; 
				std::string blockname; 

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


				questionblock->SetQuantity(quantity);
				questionblock->setX(x); 
				questionblock->setY(y);

				if (quantity <= 0)
					questionblock->SetDeflected(true); 

				ScenceManager::GetInstance()->getCurrentScence()->AddObject(questionblock);
			}
			else if (name == "Bricks")
			{
				Brick* brick = new Brick();

				TMXObject->QueryFloatAttribute("x", &x);
				TMXObject->QueryFloatAttribute("y", &y);

				brick->setX(x); 
				brick->setY(y); 

				ScenceManager::GetInstance()->getCurrentScence()->AddObject(brick); 
			}
			else
			{
				continue;
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
