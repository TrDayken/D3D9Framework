#include "Layer.h"

Layer::Layer()
{
}

Layer::Layer(TiXmlElement* TMXlayer)
{
	TMXlayer->QueryIntAttribute("id", &this->id);
	this->name = TMXlayer->Attribute("name");
	TMXlayer->QueryIntAttribute("width", &this->width);
	TMXlayer->QueryIntAttribute("height", &this->height);
	if (TMXlayer->QueryIntAttribute("visible", &this->visible))
		this->visible = 1;

	std::string layerscells = TMXlayer->FirstChildElement()->GetText();

	std::vector<std::string> tile = split(layerscells, ",");
	
	tiles = new int*[this->width];
	for (int i = 0; i < this->width; i++)
	{
		tiles[i] = new int[this->height];
		for (int j = 0; j < this->height; j++)
		{
			tiles[i][j] = stoi(tile[i + j * width]);
		}
	}
}

Layer::~Layer()
{
	for (int i = 0; i < width; i++) {
		delete[] tiles[i];
	}
	delete[] tiles;
}

int Layer::GetTileID(int x, int y)
{
	return tiles[x][y];
}

int Layer::getVisible()
{
	return this->visible;
}

int Layer::getCellcountWidth()
{
	return this->width;
}

int Layer::getCellcountHeight()
{
	return this->height;
}

std::string Layer::getName()
{
	return this->name;
}
