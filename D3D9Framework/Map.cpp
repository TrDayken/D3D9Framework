#include "Map.h"

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
			if (layer->getName() == "")
			{

			}
			this->AddLayer(layer);
		}
		
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

//this funtion is ugly and may be refine // note: multilayer cast error need to be fixed
void Map::Render(Camera* camera)
{
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
				int id = layer->GetTileID(i % width, j % height);
				if (id != 0)
				{
					tilesets->Draw(id - 1, x, y);
				}
			}
		}
	}
}

void Map::Unload()
{
	layers.clear();
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
