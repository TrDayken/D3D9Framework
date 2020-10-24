#ifndef __LAYER_H__
#define __LAYER_H__

#include "Utils.h"
#include "tinyXML/tinyxml/tinyxml.h"

class Layer
{
private:
    int id;

    std::string name;

    // the cell count of the layer;
    int width, height;

    //layer's visibility =>  0 = no, 1 = yes
    int visible;

    int** tiles;
public:
    Layer();
    Layer(TiXmlElement* TMXlayer);
    ~Layer();

    int GetTileID(int x, int y);

    std::string getName();
    
    int getCellcountWidth();
    int getCellcountHeight();

    int getVisible();
};
 
typedef Layer* LPLAYER;

#endif