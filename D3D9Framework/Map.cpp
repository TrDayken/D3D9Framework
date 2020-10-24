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
			this->AddLayer(layer);
		}
		
		DebugOut(L"[INFO] map load successful");
	}
	else
	{
		DebugOut(L"[ERROR] failed to load map");
	}

}

void Map::Update(DWORD dt)
{
}

//this funtion is ugly and may be refine // note: multilayer cast error need to fix
void Map::Render()
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
#define camx 0
#define camy 480
	int col = camx / tilewidth;
	int row = camy / tileheight;

	if (col > 0) col--;
	if (row > 0) row--;

	Vector2 camSize = Vector2(WINDOW_WIDTH / tilewidth, WINDOW_HEIGHT/ tileheight);

	for (int i = col; i < camSize.x + col + 2; i++) {
		for (int j = row; j < camSize.y + row + 2; j++) {

			int x = i * tilewidth - camx;
			int y = j * tileheight - camy;

			for (LPLAYER layer : layers) {
				//if (layer->Hidden) continue;
				int id = layer->GetTileID(i % width, j % height);
				if (id != 0)
					tilesets->Draw(id - 1, x, y);
			}
		}
	}
}

void Map::Unload()
{
	layers.clear();
}

LPTILESET Map::GetTilesetbyTileID(int ID)
{
	return tilesets;
}
