#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <d3dx9.h>

#include "Utils.h"
#include "Layer.h"
#include "TileSet.h"
#include "Global_Variable.h"
#include "tinyXML/tinyxml/tinyxml.h"
#include "Camera.h"


class Map
{
	//the cell count of the map
	int width, height;
	//the cell's width and height
	int tilewidth, tileheight;

	LPTILESET tilesets;

	std::vector<LPLAYER> layers;
public:
	Map();
	~Map();

	void AddTileSet(LPTILESET tileset);
	void AddLayer(LPLAYER layer);

	//FilePath is path to the file itself , Path = Path to storage area
	void LoadMapfromTMX(const char* FilePath, const char* Path);

	void Update(DWORD dt);
	void Render(Camera* camera);

	void Unload();

	LPTILESET GetTilesetbyTileID(int ID);
};

#endif