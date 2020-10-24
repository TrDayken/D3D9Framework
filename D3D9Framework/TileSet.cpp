#include "TileSet.h"

TileSet::TileSet()
{
}

TileSet::TileSet(TiXmlElement* TMXtileset, std::string Path)
{
	TMXtileset->QueryIntAttribute("firstgid", &this->firstgid);
	this->name = TMXtileset->Attribute("name");
	TMXtileset->QueryIntAttribute("tilewidth", &this->tilewidth);
	TMXtileset->QueryIntAttribute("tileheight", &this->tileheight);
	TMXtileset->QueryIntAttribute("tilecount", &this->tilecount);
	TMXtileset->QueryIntAttribute("columns", &this->columns);

	TiXmlElement* TMXimage = TMXtileset->FirstChildElement("image");
	std::string imagepath = Path + TMXimage->Attribute("source");
	TMXimage->QueryIntAttribute("width", &this->imagewidth);
	TMXimage->QueryIntAttribute("height", &this->imageheight);

	this->texture = Game::GetInstance()->LoadTexture(ToLPCWSTR(imagepath), NULL);
	
	int index = 0;
	for (int i = 0; i < imageheight / tileheight; i++)
	{
		for (int j = 0; j < imagewidth / tilewidth; j++,index++)
		{
			RECT* rect = new RECT();

			rect->left = j * tilewidth;
			rect->top = i * tileheight;
			rect->right = rect->left + tilewidth;
			rect->bottom = rect->top + tileheight;

			this->cells[index] = rect;

			//DebugOut(L"rect %d: %d %d %d %d \n",index, rect->left, rect->top, rect->right, rect->bottom);
		}
	}
}

TileSet::~TileSet()
{
}

int TileSet::getFirstgid()
{
	return this->firstgid;
}

void TileSet::Draw(int id, float x, float y)
{
	Game::GetInstance()->Draw(x, y, texture, cells[id]);
}

