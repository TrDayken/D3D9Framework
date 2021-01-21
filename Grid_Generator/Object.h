#pragma once

#include "tinyXML/tinyxml/tinyxml.h"


class Object
{
    int id;
    int x, y;
    int width, height;

    int cellx, celly;
    int spanx, spany;

public:
    Object();
    Object(TiXmlElement* XMLobject, int cellwidth, int cellheight);
    ~Object();

    int getID();
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    int getCellx();
    int getCelly();
    int getSpanx();
    int getSpany();

    void setID(int id);
    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);
};
