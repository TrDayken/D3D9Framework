#pragma once
class Object
{
    int id;
    int x, y;
    int width, height;

public:
    int getID();
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    void setID(int id);
    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);
};
